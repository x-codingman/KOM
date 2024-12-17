#include "klee_help.h"
#include "tx_api.h"
#include <klee/klee.h>
int main()
{
TX_MUTEX *mutex_ptr;
klee_make_symbolic_controllable(&*mutex_ptr, sizeof(*mutex_ptr), "*mutex_ptr", true);
m__txe_mutex_prioritize(*mutex_ptr);

return 0;
}