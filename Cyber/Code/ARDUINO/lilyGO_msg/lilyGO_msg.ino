#include <Arduino.h>
#include <Keyboard.h>

#define KEY_SUPERSCRIPT_TWO (136+0x35)
#define KEY_E_ACUTE         (136+0x1f)
#define KEY_E_GRAVE         (136+0x24)
#define KEY_C_CEDILLA       (136+0x26)
#define KEY_A_GRAVE         (136+0x27)
#define KEY_CIRCUMFLEX      (136+0x2f)
#define KEY_U_GRAVE         (136+0x34)

void typeKey(int key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

/* Init function */
void setup()
{
  // Begining the Keyboard stream
  Keyboard.begin(KeyboardLayout_fr_FR);
  
  // Wait 500ms
  delay(4000);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(500);
  Keyboard.println("notepad");
  delay(750);
  
  // TEXTE A AFFICHER
  Keyboard.println("Bonjour.");
  typeKey(KEY_RETURN);
  // Texte accentué : Merci d'assister à cette formation sur la cybersécurité en situation de crise ce vendredi 12 mai 2023
  Keyboard.print("Merci d'assister ");
  typeKey(KEY_A_GRAVE);
  Keyboard.print(" cette formation sur la cybers");
  typeKey(KEY_E_ACUTE);
  Keyboard.print("curit");
  typeKey(KEY_E_ACUTE);
  Keyboard.println(" en situation de crise ce vendredi 12 mai 2023.");
  typeKey(KEY_RETURN);
  Keyboard.println("===================================================================================");  
  delay(100);
  Keyboard.print("Je viens de prendre le contr");
  typeKey(KEY_CIRCUMFLEX);
   Keyboard.print("ole de votre clavier pour vous ");
  typeKey(KEY_E_ACUTE);
  Keyboard.println("crire ce message");
  Keyboard.println("===================================================================================");
  typeKey(KEY_RETURN);
  delay(100);
  Keyboard.print("Je peux m");
  typeKey(KEY_CIRCUMFLEX);
  Keyboard.print("eme lancer une application ");
  typeKey(KEY_A_GRAVE);
  Keyboard.println(" votre insu voire lancer un malware tel que Wanacry.");
  typeKey(KEY_RETURN);
  Keyboard.println("NE LAISSER PLUS VOTRE PC SANS SURVEILLANCE.");
  typeKey(KEY_RETURN);
  Keyboard.print("je vous remercie de votre compr");
  typeKey(KEY_E_ACUTE);
  Keyboard.print("hension.");
  typeKey(KEY_RETURN);
  Keyboard.println("Fabrice CRASNIER - CyberFabLab Expertises et Formations");
  typeKey(KEY_RETURN);
  // Ending stream
  
  Keyboard.end();
}

/* Unused endless loop */
void loop() {}