#include "ntshell.h"
extern "C" {
#include "ntshell_spresense_arduino.h"
}
#include "usrcmd_spresense_arduino.h"

#define PROMPT_STR ">"

static ntshell_t ntshell;


static int func_read(char* buf, int cnt, void* extobj) {
  if (Serial2.available())
    return Serial2.readBytes(buf, cnt);
  else
    return 0;
}

static int func_write(const char* buf, int cnt, void* extobj) {
  return Serial2.write(buf, cnt);
}

static int func_callback(const char* text, void* extobj) {
  return usrcmd_execute(text);
}

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
  while (!Serial2) {
    ;;
  }

  ntshell_init(
    &ntshell,
    func_read,
    func_write,
    func_callback,
    (void *)(&ntshell));

  ntshell_set_prompt(&ntshell, PROMPT_STR);

  Serial2.println("Wellcome to Spresense Arduino.\r\n type 'help' for help.");
  Serial2.print(PROMPT_STR);
  Serial2.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial2.available())
    ntshell_execute_spresense_arduino(&ntshell);
}
