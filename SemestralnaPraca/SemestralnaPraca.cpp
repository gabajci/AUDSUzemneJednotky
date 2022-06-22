#include <iostream>
#include "structures/heap_monitor.h"
#include "dataLoader.h"
#include "state.h"
#include <fcntl.h>
#include "customFilter.h"
#include <io.h>
#include "Inicializator.h"

int main()
{
    initHeapMonitor();

    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
   
    Inicializator start;

    return 0;
}


// symbolicke konstanty vsade


