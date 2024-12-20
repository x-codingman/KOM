#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_MUTEX *mutex_ptr;
klee_make_symbolic_controllable(&*mutex_ptr, sizeof(*mutex_ptr), "*mutex_ptr", true);
ULONG wait_option;
klee_make_symbolic_controllable(&wait_option, sizeof(wait_option), "wait_option", true);
m__txe_mutex_get(*mutex_ptr, wait_option);

return 0;
}