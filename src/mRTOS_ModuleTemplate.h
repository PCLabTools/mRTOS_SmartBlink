#include <Arduino.h>
#include <microRTOS.h>

#ifndef mRTOS_ModuleTemplate_h
  #define mRTOS_ModuleTemplate_h

  class mRTOS_ModuleTemplate : public microRTOS
  {
    public:
      mRTOS_ModuleTemplate(const char* identity);
      uint8_t run();
    
    protected:
      static void main_loop(void*);
  };

#endif