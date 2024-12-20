#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_EVENT_FLAGS_GROUP *group_ptr;
klee_make_symbolic_controllable(&*group_ptr, sizeof(*group_ptr), "*group_ptr", true);
CHAR **name;
klee_make_symbolic_controllable(&**name, sizeof(**name), "**name", true);
ULONG *current_flags;
klee_make_symbolic_controllable(&*current_flags, sizeof(*current_flags), "*current_flags", true);
TX_THREAD **first_suspended;
klee_make_symbolic_controllable(&**first_suspended, sizeof(**first_suspended), "**first_suspended", true);
ULONG *suspended_count;
klee_make_symbolic_controllable(&*suspended_count, sizeof(*suspended_count), "*suspended_count", true);
TX_EVENT_FLAGS_GROUP **next_group;
klee_make_symbolic_controllable(&**next_group, sizeof(**next_group), "**next_group", true);
m__txe_event_flags_info_get(*group_ptr, **name, *current_flags, **first_suspended, *suspended_count, **next_group);

return 0;
}