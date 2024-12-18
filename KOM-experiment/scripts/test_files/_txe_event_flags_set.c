#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_EVENT_FLAGS_GROUP *group_ptr;
klee_make_symbolic_controllable(&*group_ptr, sizeof(*group_ptr), "*group_ptr", true);
ULONG flags_to_set;
klee_make_symbolic_controllable(&flags_to_set, sizeof(flags_to_set), "flags_to_set", true);
UINT set_option;
klee_make_symbolic_controllable(&set_option, sizeof(set_option), "set_option", true);
m__txe_event_flags_set(*group_ptr, flags_to_set, set_option);

return 0;
}