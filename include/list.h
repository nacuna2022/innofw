/*
 * utils.h
 *
 *  Created on: Aug 16, 2022
 *      Author: alvin.abitria
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>

struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

static inline void list_init (struct list_head *list)
{
	list->next = list;
	list->prev = list;
}


static inline void __list_add (struct list_head *new, struct list_head *prev, struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}


// Add to head of the list
static inline void list_add (struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}


static inline void __list_del (struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}


static inline void __list_del_entry (struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}


static inline void list_del (struct list_head *entry)
{
	__list_del_entry(entry);
	entry->next = NULL;
	entry->prev = NULL;
}

static inline int list_is_head(const struct list_head *list, const struct list_head *head)
{
	return list == head;
}


static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

static inline struct list_head *list_remove_head(struct list_head *head)
{
        struct list_head *p = NULL;
        if (!list_is_head(head, head->next)) {
                p = head->next;
                list_del(p);
        }
        return p;
}

static inline void __list_splice(struct list_head *list,
                                 struct list_head *prev,
                                 struct list_head *next)
{
        struct list_head *first = list->next;
        struct list_head *last = list->prev;

        first->prev = prev;
        prev->next = first;

        last->next = next;
        next->prev = last;
}

static inline void list_splice_init(struct list_head *list,
                                    struct list_head *head)
{
        if (!list_empty(list)) {
                __list_splice(list, head, head->next);
                list_init(list);
        }
}

static inline struct list_head *list_peek_head(struct list_head *list)
{
        struct list_head *head = NULL;
        if (!list_empty(list)) {
                head = list->next;
        }
        return head;
}

/*
 * Loop to iterate on each entry; safe for list deleting providing the list being deleted
 * is the list being iterated; only the list pointed to by 'pos' can be removed.
 */
#define list_for_each_safe(pos, N, head) \
	for (pos = (head)->next, N = pos->next; \
	     !list_is_head(pos, (head)); \
	     pos = N, N = pos->next)

#define list_for_each(pos, head) \
        for (pos = (head)->next; !list_is_head(pos, (head)); pos = pos->next)

#define offset_of(type, member)		((size_t)&((type *)0)->member)

#define container_of(ptr, type, member)	({      \
	void *mptr = (void *)(ptr);             \
        ((type *)(mptr - offset_of(type, member)));})

#endif /* __UTILS_H__ */
