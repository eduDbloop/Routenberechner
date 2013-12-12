#include "display_joystick.h"
#include <stdbool.h>

static const char orte[][9] = 
{"Astadt", "Bfeld", "Cburg", "Ddorf", "Ehausen", "Ffurt", "Ghagen"};
static const int anzahlOrte = sizeof orte / sizeof(char[9]);

struct Verbindung
{
  int ort1;
  int ort2;
  int distanz;
};

typedef struct Verbindung Verbindung;

static const Verbindung verbindungen[] =
{ {1,2,6}, {3,4,100}, {0,5,3}, {4,5,22}, {4,2,8}, {1,4,3}, {1,3,4}, {5,3,128} };
static const int anzahlVerbindungen = sizeof verbindungen / sizeof(Verbindung);

int waehleOrt(int a) // a = Nummer des zunächst sichtbaren Orts
{
  writeString(orte[a]);
  while(readAnalog(0) < 800) // Joystick nicht rechts
  {
    if(readAnalog(1) > 700) // Joystick oben
    {
      a++;
      if(a >= anzahlOrte)
      {
        a = 0;
      }
      writeString(orte[a]);
    }
    while(readAnalog(1) > 700) // auf Loslassen warten
    {
      waitMilliseconds(50);
    }
  }
  while(readAnalog(0) > 700) // auf Loslassen warten
  {
    waitMilliseconds(50);
  }
  
  return a;
}

int main( void )
{
  initialize();
  
  while(true)
  {
    int start = waehleOrt(3);
    int ziel = waehleOrt(5);
    writeString("Suche...");
    
    int route[] = {start, 0, 0, 0, 0, 0};
    int maximaleLaengeDerRoute = sizeof route / sizeof(int);
    int besteRoute[sizeof route / sizeof(int)];
    bool eineRouteGefunden = false;
    int laengeDerBestenRoute;
    
    
    
    // Hier kommt Ihr Programmcode hin!
    bool fertig = false;
    bool erreicht = false;
    while(!fertig)
    {
      for(int a=0;a<anzahlVerbindungen || eineRouteGefunden == true; a++)
        { 
          if (verbindungen[a].ort1 == start || verbindungen[a].ort2 == start)
          {
            if (verbindungen[a].ort1 == ziel || verbindungen[a].ort2 == ziel) {
              eineRouteGefunden =true;
            }
          }
        }
      while(!erreicht) {
          
      }
      
      int o = maximaleLaengeDerRoute-1;
      while(route[o] == anzahlOrte-1)
      {
        route[o] = 0;
        o--;
        if(o==0)
        {
          fertig=true;
          break;
        }
      }
      route[o]++;
    }
    
    if(eineRouteGefunden)
    {
      writeString("km-Zahl:");
      waitMilliseconds(500);
      writeNumber(laengeDerBestenRoute);
      waitMilliseconds(500);
      for(int i = 0; besteRoute[i] != ziel; i++)
      {
        writeString(orte[besteRoute[i]]);
        waitMilliseconds(500);
      }
      writeString(orte[ziel]);
      waitMilliseconds(500);
    }
    else
    {
      writeString("Nichts.");
      waitMilliseconds(500);      
    }
    writeString("Fertig.");
    waitMilliseconds(500);  
  } 
  
  //return 0;
}
