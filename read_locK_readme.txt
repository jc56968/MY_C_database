read_lock
1.for find()  only read_lock  add p->next; release p;
1.for update()   read_lock+write_lock  add p->next; release p; if(p==node) write_lock;
1.for insert()  carbbing stratage only write_lock add p->next; release p(if p->size<=node_size-2);//using stack to help store father node'slock
1.for delete()  carbbing stratage only write_lock add p->next; release p(if p->size<=node_size-2);//using stack to help store father node'slock