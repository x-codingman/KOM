#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_EVENT_FLAGS_GROUP *group_ptr;
klee_make_symbolic_controllable(&*group_ptr, sizeof(*group_ptr), "*group_ptr", true);
m__txe_event_flags_set_notify(*group_ptr, );

return 0;
}