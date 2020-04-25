
extern "C" {
#include "SysCallLib.h"
#include "ms3690_lib.h"
#undef FILE
}
#include "AppWorker.h"

extern "C" {
int user_main(void) {
  AppWorker worker;
  try {
    worker.Run();
  } catch (...) {
    // TODO: Implement developer-frindly exception handling
  }
  return 0;
}
}
