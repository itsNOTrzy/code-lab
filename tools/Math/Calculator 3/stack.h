#include "common.h"


extern NODE *OperandHead,*OperatorHead;


NODE *PushOperand (
	NODE *Source
	);

NODE *PopOperand (
	void
	);

NODE *PushOperator (
	NODE *Source
	);

NODE *PopOperator (
	void
	);

void ClearStack (
	void
	);