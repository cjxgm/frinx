
#ifndef __KE_LINK_H__
#define __KE_LINK_H__




#define LINKABLE(TYPE)	\
	TYPE * prev; \
	TYPE * next;


// example:
// 		{ TRAVERSE(link, Type, p) {
// 			// do something with "p"
// 		}}
#define TRAVERSE(LNK, TYPE, V) \
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

