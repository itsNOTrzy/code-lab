#include "common.h"
#include "stack.h"


NODE *OperandHead = NULL;
NODE *OperatorHead = NULL;


NODE *PushOperand (
	NODE *Source
	)
{
	NODE *tmp;
	tmp = (NODE*) malloc (sizeof (NODE));
	if (tmp == NULL) {
		return NULL;
	}
	NODEcopy (tmp,Source);
	tmp->Next = OperandHead;
	OperandHead = tmp;
	return OperandHead;
}

NODE *PopOperand (
	void
	)
{
	NODE *temp = OperandHead;
	if (OperandHead == NULL) {
		error = the_stack_is_null;
		return NULL;
	}
	OperandHead = OperandHead->Next;
	return temp;
}

NODE *PushOperator (
	NODE *Source
	)
{
	NODE *tmp;
	tmp = (NODE*) malloc (sizeof (NODE));
	if (tmp == NULL) {
		return NULL;
	}
	NODEcopy (tmp,Source);
	tmp->Next = OperatorHead;
	OperatorHead = tmp;
	return OperatorHead;
}

NODE *PopOperator (
	void
	)
{
	NODE *temp = OperatorHead;
	if (OperandHead == NULL) {
		error = the_stack_is_null;
		return NULL;
	}
	OperatorHead = OperatorHead->Next;
	return temp;
}

void ClearStack (
	 void
	)
{
	DeleteList (OperandHead);
	DeleteList (OperatorHead);
	OperandHead = NULL;
	OperatorHead = NULL;
}