#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main() {
  const char *filepath = "/sys/class/power_supply/";
  const char *prefix = "BAT";
  
  long max = 0;
  long now = 0;
  long tempmax = 0;
  long tempnow = 0;
  
  int batterycount = 0;
  DIR *dir = opendir(filepath);

  if (dir == NULL) {
    printf("Opening directory failed");
    return 1;
  }
  
  char buff[256];
  struct dirent *entry;
  
  while ((entry = readdir(dir)) != NULL) {
      if ((strncmp(entry->d_name, prefix, strlen(prefix)) == 0)) {
	  batterycount++;
	  snprintf(buff, sizeof(buff), "%s/%s/capacity", filepath, entry->d_name);
	  FILE *f = fopen(buff, "r");
	  
	  if(f != NULL) {
	    
	    int capacity = 0;
	    if (fscanf(f,"%d", &capacity) == 1) {
	      printf("Battery [%s] Capacity: %d%\n", entry->d_name, capacity);
	    }

	    fclose(f);
	  }

	  snprintf(buff, sizeof(buff), "%s%s/energy_full", filepath, entry->d_name);

	  f = fopen(buff, "r");

	  if(f != NULL) {
	    
	    if(fscanf(f, "%ld", &tempmax) == 1) {
	      max += tempmax;
	    }

	    fclose(f);
	  }

	  snprintf(buff, sizeof(buff), "%s%s/energy_now", filepath, entry->d_name);

	  f = fopen(buff, "r");

	  if(f != NULL) {
	    
	    if(fscanf(f, "%ld", &tempnow) == 1) {
	      now += tempnow;
	    }
	    
	    fclose(f);
	  }

      }
  }
  if (batterycount == 0) printf("No batteries found");
  printf("Batteries: %d\n", batterycount);
  // printf("%d\n", now);
  // printf("%d\n", max);
  int overall = (now * 100) / max;
  printf("Battery: %d%\n", overall);

  return 0;
    
}
