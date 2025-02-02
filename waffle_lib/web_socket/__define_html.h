#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include "__utils.h"


typedef struct {
  char* title;
  union {
    uint32_t* RGB_BACKGROUND[2];
    uint32_t* RGBA_BACKGROUND[3];
  };

} *WEB_SCHEM_INTERFACE;


char* config_file = ".htconfig";

const char* TAILWINDCSS_CDN_URL = "https://cdn.tailwindcss.com";
const char* tags[] = {
  "<title> </title>",
  "<script src=\"%s\"> </script>",
  "<h%d class=\"%s\" id=\"%s\" style=\"%s\"> <h%d>",
  "<img src=\"%s\" alt=\"%s\" style=\"%s\" id=\"%s\" />"
  "<a class=\"%s\" id=\"%s\" href=\"%s\"> </a>",
  "<p class=\"%s\" id=\"%s\"> </p>",

};

char BUFFER_LANG[2];
std::string LOCALE_LANG = std::locale().name();
#define USER_LOCALE snprintf(BUFFER_LANG, 3, "%s", LOCALE_LANG);

void INIT_HTML(const char* TitleTag_Content, const char* filename = config_file) {

  char* append_tailwind;
  char* buffer_RouteName;
  snprintf(append_tailwind, sizeof(append_tailwind), tags[1], TAILWINDCSS_CDN_URL);

}



