/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project


  */



#include "GoGL.h"





Effect::Effect()
{
	next = NULL;
}

Effect::~Effect()
{
	//if (next != NULL) delete next;
}


int Effect::pulse()
{
	return 0;
}

int Effect::type()
{
	return TYPE_NONE;
}




EffectList::EffectList()
{
	list = NULL;
}


EffectList::~EffectList()
{
	if (list != NULL) delete list;
}

void EffectList::addEffect(Effect* e)
{
	e->next = list;
	list = e;
}

void EffectList::pulse()
{
	Effect* holder = NULL;
	Effect* temp = list;
	Effect* prev = NULL;

	while (temp != NULL)
	{
		holder = NULL;
		int retval = temp->pulse();
		if (!retval) 
		{
			if (prev == NULL)
				list = temp->next;
			else
				prev->next = temp->next;

			holder = temp;	
			//printf("killing\n");
		}
		if (holder == NULL) prev = temp;
		temp = temp->next;
		if (holder != NULL) delete holder;
	}

}