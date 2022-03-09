#include "mRTOS_ModuleTemplate.h"

mRTOS_ModuleTemplate::mRTOS_ModuleTemplate(const char* identity)
{
  #if defined microRTOS_DEBUG && microRTOS_DEBUG > 0
    printf("mRTOS_ModuleTemplate(identity=\"%s\")\n", identity);
  #endif
  id = identity;
}

uint8_t mRTOS_ModuleTemplate::run()
{
  #if defined microRTOS_DEBUG && microRTOS_DEBUG > 0
    printf("%s: run()\n", id);
  #endif
  microRTOS::run(&main_loop);
  return 0;
}

void mRTOS_ModuleTemplate::main_loop(void* pModule)
{
  mRTOS_ModuleTemplate* mod = (mRTOS_ModuleTemplate*)pModule;
  #if defined microRTOS_DEBUG && microRTOS_DEBUG > 0
    printf("%s: main_loop(pModule=%p) - core(%d)\n", mod->id, pModule, xPortGetCoreID());
  #endif
  for ( ;; )
  {
    const char* message = "";
    xQueueReceive(mod->hCommand, &message, 1000 / portTICK_PERIOD_MS);
    if (!strcmp(message, ""))
    {
      #if defined microRTOS_DEBUG && microRTOS_DEBUG > 0
        printf("%s: main_loop(timeout)\n", mod->id);
      #endif
      continue;
    }
    else
    {
      #if defined microRTOS_DEBUG && microRTOS_DEBUG > 0
        printf("%s: main_loop(message: %s)\n", mod->id, message);
      #endif
      String response = "";
      moduleMessage incoming = mod->interface.parse(message);
      if (incoming.state == "id?")
      {
        response = String(mod->id) + " [mRTOS_ModuleTemplate]";
      }
      else
      {
        response = "ERROR - No State: \"" + incoming.state + "\" (message data: " + incoming.data + ")";
      }
      xQueueSend(mod->hResponse, &response, portMAX_DELAY);
    }
  }
}