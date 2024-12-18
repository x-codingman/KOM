#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_MUTEX *mutex_ptr;
klee_make_symbolic_controllable(&*mutex_ptr, sizeof(*mutex_ptr), "*mutex_ptr", true);
CHAR **name;
klee_make_symbolic_controllable(&**name, sizeof(**name), "**name", true);
ULONG *count;
klee_make_symbolic_controllable(&*count, sizeof(*count), "*count", true);
TX_THREAD **owner;
klee_make_symbolic_controllable(&**owner, sizeof(**owner), "**owner", true);
TX_THREAD **first_suspended;
klee_make_symbolic_controllable(&**first_suspended, sizeof(**first_suspended), "**first_suspended", true);
ULONG *suspended_count;
klee_make_symbolic_controllable(&*suspended_count, sizeof(*suspended_count), "*suspended_count", true);
TX_MUTEX **next_mutex;
klee_make_symbolic_controllable(&**next_mutex, sizeof(**next_mutex), "**next_mutex", true);
m__txe_mutex_info_get(*mutex_ptr, **name, *count, **owner, **first_suspended, *suspended_count, **next_mutex);

return 0;
}