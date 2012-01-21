
#ifndef ___KE_LINK_H___
#define ___KE_LINK_H___




#define LINKABLE(TYPE)	\
	TYPE * prev; \
	TYPE * next;


#define TRAVERSE(TYPE, V, LNK) \
	TYPE * V = (TYPE *)LNK; \
	while ((V = V->next) != (TYPE *)LNK)



typedef struct Link
{
	LINKABLE(struct Link);
}
Link;




void link_init(Link * lnk);
void link_addtail(Link * lnk, void * data);
void link_addhead(Link * lnk, void * data);
void link_remove(void * data);
void link_delete(void * data);




#endif

