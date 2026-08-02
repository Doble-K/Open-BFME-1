# How BFME 1.03 loads an INI file

`docs/ini_schema.md` says what the blocks and fields are. This says what the
loader does with them, which matters for anyone writing a mod because it decides
what a syntax error looks like, when an override wins, and where `#define` may
and may not appear.

Every claim below is read out of `lotrbfme.exe`. Four of the five functions are
reproduced as C++ that assembles to retail's exact bytes. The fifth, `prepFile`,
is byte-exact too but only as a MASM dump -- it has not been recovered as C++
yet -- so what this page says about it is read off the disassembly rather than
off source. That is a weaker standard and is flagged where it applies.

## The pipeline

`INI::load` (0x00853A20, byte-exact C++) is the entry point. Everything that reads
an INI goes through it:

```cpp
void INI::load( AsciiString filename, INILoadType loadType, Xfer *pXfer )
{
    setFPMode();                    // consistent Reals, so parsing is deterministic
    s_xfer = pXfer;
    prepFile( filename, loadType ); // open, slurp, close, expand macros
    try {
        while( m_endOfFile == FALSE ) {
            readLine();
            parseLine( filename );
        }
    }
    catch( INIException& e ) { throw INIException( e.m_argCount, "%s\n\nError parsing INI block '%s' in file '%s'.", ... ); }
    catch( ... )             { unPrepFile(); throw; }
    unPrepFile();
}
```

The shape to notice is that **the file is not streamed**. `prepFile` reads the
whole thing into an array of lines and closes the handle before a single block is
parsed; `readLine` then walks that array. Zero Hour reads through an 8 KB buffer
as it parses, and BFME does not have that buffer at all.

That is not a stylistic difference. The macro pass below needs to rewrite lines
before any of them are parsed, which a streaming reader cannot do.

| step | address | size | status |
|:--|:--|--:|:--|
| `INI::load` | 0x00853A20 | 259 | byte-exact C++ |
| `INI::prepFile` | 0x00853610 | 1037 | byte-exact as a MASM dump; no C++ yet |
| `INI::readLine` | 0x008514C0 | 121 | byte-exact C++ |
| `INI::parseLine` | 0x00851350 | 362 | byte-exact C++ |
| `INI::unPrepFile` | 0x00850E30 | 50 | byte-exact C++ |

## Reading a line

`readLine` copies the next entry out of the line array into `m_buffer`, capped at
`INI_MAX_CHARS_PER_LINE`, and sets `m_endOfFile` when it runs out. If an `Xfer`
was passed to `load`, every line is fed through it — that is how a replay or a
network game proves both machines parsed identical INI text.

## Dispatching a line

`parseLine` takes the first whitespace-separated word of the line and looks it up
in the block registry (a linked list of `{keyword, parser}` nodes; see
`tools/dump_ini_schema.py`). If it matches, the line is copied into
`m_curBlockStart` and the block parser is invoked.

The errors are BFME's own. Zero Hour formats one message into a 1 KB stack
buffer; BFME throws a variadic `INIException` at three separate sites, and these
are the exact texts a mod author sees:

```
Unknown block '%s'.\n\nError parsing INI block '%s' in file '%s'.
%s\n\nError parsing INI block '%s' in file '%s'.
Unknown error parsing INI block '%s' in file '%s'.
```

The first fires when the keyword is not in the registry — so a typo'd block name
reports the block, not the field. The second wraps whatever the block parser
itself threw, prefixing that parser's own message. The third is the catch-all.

All three name the file from `INI::m_filename`, not from the filename passed in.

## `#define` macros

This is BFME-only; Zero Hour has no equivalent. Everything in this section comes
from reading `prepFile`'s disassembly, not from reproduced source. `prepFile` walks the loaded lines
before parsing starts and expands macros, which is why they work anywhere in the
file rather than only above their use.

A macro line is one that **starts with** `#define`. The rules are enforced with
one message each, and they are the strings in `prepFile`:

| rule | message |
|:--|:--|
| not permitted in `map.ini` | `%s:\nMACROs not allowed in map.ini.\n%s.` |
| the name must be uppercase | `%s:\nMACRO names must use UPPERCASE letters.\n%s.` |
| the name needs a value | `%s:\nError parsing MACRO.\n%s has no value` |
| a name may be defined once | `%s:\nDuplicate MACRO names.\n%s.` |

The uppercase rule is checked by scanning the macro name for any character in
`a`–`z`, so a name is rejected for containing a lowercase letter anywhere, not
merely for starting with one. The `map.ini` rule is a suffix test on the
filename, so it catches any path ending in `map.ini`.

A `#define` line is blanked in place once recognised — the array entry's first
byte is set to NUL — so the parser never sees it and the line numbers reported in
errors still line up with the file on disk.

## Opening

`prepFile` opens through `TheFileSystem->openFile( filename.str(), File::READ )`.
Two failures are distinguished, and both are exceptions rather than Zero Hour's
debug-only assertions:

```
INI::load, cannot open file '%s', file already open
INI::load, cannot open file '%s'
```

The first means an `INI` object was reused while still loading.

## Tearing down

`unPrepFile` frees the line array, sets `m_filename` to `"None"`, and zeroes
`m_loadType`, `m_lineNum`, `m_endOfFile` and `s_xfer`. It closes no file, because
`prepFile` already did.

It runs on both paths — the `catch(...)` in `load` calls it before rethrowing —
so a failed INI leaves the loader reusable. The `catch(INIException&)` path is
the exception: it rethrows without tearing down, which is retail's behaviour, not
an omission here.
