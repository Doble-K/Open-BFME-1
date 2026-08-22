namespace D3DXShader
{
	class CShaderProgram
	{
	protected:
		long EmitDSX();
		long EmitDSY();
		long EmitMIN();
		long EmitMAX();
		long EmitLT();
		long EmitGE();
		long EmitADD();
		long EmitMUL();
		long EmitDST();

		long EmitInstSimple(unsigned long opcode);
	};

	long CShaderProgram::EmitDSX() { return EmitInstSimple(0x5b); }
	long CShaderProgram::EmitDSY() { return EmitInstSimple(0x5c); }
	long CShaderProgram::EmitMIN() { return EmitInstSimple(0x0a); }
	long CShaderProgram::EmitMAX() { return EmitInstSimple(0x0b); }
	long CShaderProgram::EmitLT() { return EmitInstSimple(0x0c); }
	long CShaderProgram::EmitGE() { return EmitInstSimple(0x0d); }
	long CShaderProgram::EmitADD() { return EmitInstSimple(0x02); }
	long CShaderProgram::EmitMUL() { return EmitInstSimple(0x05); }
	long CShaderProgram::EmitDST() { return EmitInstSimple(0x11); }
}
