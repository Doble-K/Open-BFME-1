struct RvaA3020Offset656Getter
{
    unsigned char unused[656];
    unsigned int value;

    unsigned int get_value();
};

unsigned int RvaA3020Offset656Getter::get_value()
{
    return value;
}
