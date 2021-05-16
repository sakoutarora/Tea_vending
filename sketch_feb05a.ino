
#include "U8glib.h"
#define OK_PIN  22    //D35
#define UP_PIN 24   //D33 
#define DOWN_PIN 26   //
#define LCD_EN 3          //  23
#define LCD_MOSI 4        //  17
#define LCD_CS 5          //  16

int State = 0;
String enr = "100";  // SW DATA CLOCK for incoder appending 
char first_menu[3][15] = {"New Tea","Saved Profile","Back"};
char third_menu[3][8] = {"Small","Medium","Large"};
char masalas[10][25] = {"Cinnamon","Staranise","Ginger","Cloves","Cardmom","Fennel Seeds","Lemon Grass","Tea Leaves","BACK","NEXT"}; 
char masala_selected[9][25] = {"NONE","NONE","NONE","NONE","NONE","NONE","NONE","NONE"};
char third_2_menu[4][15] = {"Small","Medium","Large","NONE"};
char milk[2][10] = {"YES","NO"};
int ar_masala[9] = {0,0,0,0,0,0,0,0,0};

unsigned long last_OK_DebounceTime = 0; 

int ok_buttonState = LOW; 
int up_buttonState = LOW;
int down_buttonState = LOW;  

int last_OK_ButtonState = LOW;
int last_UP_ButtonState = LOW;  
int last_DOWN_ButtonState = LOW;  


unsigned long debounceDelay = 50; 

unsigned long last_UP_DebounceTime = 0;
unsigned long last_DOWN_DebounceTime = 0; 


int h = 0;
int w = 0;
int first_menu_pos = 0;
int third_menu_pos = 0;
int masala_pos = 0;
int third_sec_pos = 0;
int third_three_pos = 0;

int chng = 0 ;

bool chup = false;
bool chdw = false;
bool chok = false;


int glass_size = 0;
int milks = 0;

U8GLIB_ST7920_128X64_4X u8g(LCD_EN, LCD_MOSI, LCD_CS); // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
void draw_initial(void) 
{
  
 
  u8g.setFont(u8g_font_osb21);
  w = u8g.getStrWidth("Amrut");
  h = u8g.getFontAscent()-u8g.getFontDescent();
  u8g.drawRFrame(18,18,w+4,h+4,2);
  u8g.setFontPosTop();
  u8g.drawStr(20,20, "Amrut");  
}


void btn_pressed ()
{
  //Serial.print("OK button funcrion ");
  int reading = digitalRead(OK_PIN);
  //Serial.println(reading);
  


  if (reading != last_OK_ButtonState) 
  {
    //Serial.println("inside first if ");
    last_OK_DebounceTime = millis();
  }

  if (( millis() - last_OK_DebounceTime) > debounceDelay) 
  {
    //Serial.println("inside if if");
    if (reading != ok_buttonState) 
    {
      ok_buttonState = reading;

      if (ok_buttonState == HIGH) {
        chok = true;
      }
    }
  }
  last_OK_ButtonState = reading;
}

void up_pressed ()
{
  int reading = digitalRead(UP_PIN);
//  Serial.print("UP READING :");
//  Serial.println(reading);


  if (reading != last_UP_ButtonState) {

    last_UP_DebounceTime = millis();
  }

  if ((millis() - last_UP_DebounceTime) > debounceDelay) 
  {
    if (reading != up_buttonState) 
    {
      up_buttonState = reading;

      if (up_buttonState == HIGH) {
        chup = true;
      }
    }
  }
  last_UP_ButtonState = reading;
}

void down_pressed ()
{
  int reading = digitalRead(DOWN_PIN);
//  Serial.print("DOWN READING :");
//  Serial.println(reading);

  if (reading != last_DOWN_ButtonState) {

    last_DOWN_DebounceTime = millis();
  }

  if ((millis() - last_DOWN_DebounceTime) > debounceDelay) 
  {
    if (reading != down_buttonState) 
    {
      down_buttonState = reading;

      if (down_buttonState == HIGH) {
        chdw =  true;
      }
    }
  }
  last_DOWN_ButtonState = reading;
}

void drawFifthmenu()
{
  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  u8g.drawStr(18,18,"PREPARING ... ");
  
  
}


void drawFirstmenu()
{
  uint8_t i ;
  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  int w1 = u8g.getStrWidth(first_menu[0]);
  int w2 = u8g.getStrWidth(first_menu[1]);
  int w3 = u8g.getStrWidth(first_menu[2]);


  u8g.drawStr(10,15,first_menu[0]);
  u8g.drawStr(10,30,first_menu[1]);
  u8g.drawStr(10,45,first_menu[2]);

  for ( i=0 ; i<3 ; i++)
  {
    if ( i == first_menu_pos)
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(8,13,w1+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(8,28,w2+4,h+4,2);
      }
      if (i==2)
      {
        u8g.drawRFrame(8,43,w3+4,h+4,2);
      }
    }
  }
  
}

void drawFourthmenu()
{
  u8g.setFontPosTop();
  u8g.drawStr(20,20, "Fourth Software State"); 
  
}

void drawThirdmenu()
{
  uint8_t i ;
  u8g.setFontPosTop();
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  int w1 = u8g.getStrWidth(third_menu[0]);
  int w2 = u8g.getStrWidth(third_menu[1]);
  int w3 = u8g.getStrWidth(third_menu[2]);
  
  u8g.drawStr(5,5, "Glass Size");
  u8g.drawStr(5,20,third_menu[0]);
  u8g.drawStr(5,35,third_menu[1]);
  u8g.drawStr(5,50,third_menu[2]); 
  for ( i=0 ; i<3 ; i++)
  {
    if ( i == third_menu_pos)
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(3,18,w1+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(3,33,w2+4,h+4,2);
      }
      if (i==2)
      {
        u8g.drawRFrame(3,48,w3+4,h+4,2);
      }
    }
  }
}

void drawThird1menu()
{

  Serial.print("Inside this function ");
  Serial.println(masala_pos);
  u8g.setFontPosTop();
  u8g.drawStr(5,5, "Masalas");
  uint8_t i ;
  u8g.setFontRefHeightText();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  int w1 = u8g.getStrWidth(masalas[0]);
  int w2 = u8g.getStrWidth(masalas[1]);
  int w3 = u8g.getStrWidth(masalas[2]);
  int w4 = u8g.getStrWidth(masalas[3]);
  int w5 = u8g.getStrWidth(masalas[4]);
  int w6 = u8g.getStrWidth(masalas[5]);
  int w7 = u8g.getStrWidth(masalas[6]);
  int w8 = u8g.getStrWidth(masalas[7]);
  int w9 = u8g.getStrWidth(masalas[8]);
  int w10 = u8g.getStrWidth(masalas[9]); 



  if (masala_pos > 8)
  {
    u8g.setFontPosTop();
    u8g.drawStr(5,20,masalas[9]);
    u8g.drawRFrame(3,18,w10+4,h+4,2);
  }


  if (masala_pos > 5 and masala_pos <= 8)
  {
    u8g.drawStr(5,5, "Masalas");
    u8g.setFontPosTop();
    u8g.drawStr(5,20,masalas[6]);
    u8g.drawStr(5,35,masalas[7]);
    u8g.drawStr(5,50,masalas[8]);

    u8g.drawStr(90,20,masala_selected[6]);
    u8g.drawStr(90,35,masala_selected[7]);
    u8g.drawStr(90,50,masala_selected[8]);

    


    for ( i=0 ; i<3 ; i++)
  {
    if ( i == ( masala_pos - 6 ))
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(3,18,w7+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(3,33,w8+4,h+4,2);
      }
      if (i==2)
      {
        u8g.drawRFrame(3,48,w9+4,h+4,2);
      }
    }
  }
    
  }
  
  if (masala_pos > 2 && masala_pos <= 5 )
  {
    u8g.drawStr(5,5, "Masalas");
    
    u8g.drawStr(5,20,masalas[3]);
    u8g.drawStr(5,35,masalas[4]);
    u8g.drawStr(5,50,masalas[5]);
    
    u8g.drawStr(90,20,masala_selected[3]);
    u8g.drawStr(90,35,masala_selected[4]);
    u8g.drawStr(90,50,masala_selected[5]);

    for ( i=0 ; i<3 ; i++)
  {
    if ( i == (masala_pos - 3 ))
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(3,18,w4+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(3,33,w5+4,h+4,2);
      }
      if (i==2)
      {
        u8g.drawRFrame(3,48,w6+4,h+4,2);
      }
    }
  }
    
    
  }

  if (masala_pos <= 2 ){
  u8g.drawStr(5,5, "Masalas");
  
  u8g.drawStr(5,20,masalas[0]);
  u8g.drawStr(5,35,masalas[1]);
  u8g.drawStr(5,50,masalas[2]);

  u8g.drawStr(90,20,masala_selected[0]);
  u8g.drawStr(90,35,masala_selected[1]);
  u8g.drawStr(90,50,masala_selected[2]);

  for ( i=0 ; i<3 ; i++)
  {
    if ( i == masala_pos)
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(3,18,w1+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(3,33,w2+4,h+4,2);
      }
      if (i==2)
      {
        u8g.drawRFrame(3,48,w3+4,h+4,2);
      }
    }
  }

  
    
  } 
}


void update_masala()
{
  uint8_t i ;
  
  for (i=0 ; i<8 ; i++){

     if (ar_masala[i] == 0 )
    {
      strcpy(masala_selected[i],"NONE");
    }
    
    if (ar_masala[i] == 1 )
    {
      strcpy(masala_selected[i],"SMALL");
    }
    if (ar_masala[i] == 2 )
    {
      strcpy(masala_selected[i],"MEDIUM");
    }
    if (ar_masala[i] == 3 )
    {
      strcpy(masala_selected[i],"LARGE");
    }
     
  }
}



void drawThird2menu()
{
  uint8_t i ;
  u8g.setFontPosTop();
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  
  int w1 = u8g.getStrWidth(third_2_menu[0]);
  int w2 = u8g.getStrWidth(third_2_menu[1]);
  int w3 = u8g.getStrWidth(third_2_menu[2]);
  int w4 = u8g.getStrWidth(third_2_menu[3]);
  
  u8g.drawStr(5,5,third_2_menu[0]);
  u8g.drawStr(5,20,third_2_menu[1]);
  u8g.drawStr(5,35,third_2_menu[2]); 
  u8g.drawStr(5,50,third_2_menu[3]); 
  
  for ( i=0 ; i<4 ; i++)
  {
    if ( i == third_sec_pos)
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(3,3,w1+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(3,18,w2+4,h+4,2);
      }
      if (i==2)
      {
        u8g.drawRFrame(3,33,w3+4,h+4,2);
      }
      if (i==3)
      {
        u8g.drawRFrame(3,48,w3+4,h+4,2);
      }
    }
  }
}

void drawThird3menu(){
  
  u8g.setFontPosTop();
  u8g.drawStr(5,5, "MILK");
  uint8_t i ;
  u8g.setFontRefHeightText();
  h = u8g.getFontAscent()-u8g.getFontDescent();
  int w1 = u8g.getStrWidth(masalas[0]);
  int w2 = u8g.getStrWidth(masalas[1]);
  u8g.drawStr(5,20,milk[0]);
  u8g.drawStr(5,35,milk[1]);

  for ( i=0 ; i<2 ; i++)
  {
    if ( i == third_three_pos)
    {
      if ( i == 0 )
      {
        u8g.drawRFrame(3,18,w1+4,h+4,2);
      }
      if ( i == 1 )
      {
        u8g.drawRFrame(3,33,w2+4,h+4,2);
      }
    }
  }
  
  
}



void setup(void) 
{
  Serial.begin(9600);
  pinMode(OK_PIN, INPUT);
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  
}

void loop(void) 
{
  if (State == 0)
  {
    chok = false;
    Serial.print("Software State is ");
    Serial.println(State);
    u8g.firstPage();  
    do 
    {
      draw_initial();
    }while( u8g.nextPage());  
    btn_pressed();
    //Serial.println(chok);
    if (chok)
    {
      State = 1;
      delay(1000);
    }
    //delay(10);
  }

  if (State == 1) 
  {
    Serial.print("Software state :");
    Serial.println(State);
    u8g.firstPage();
    do
    {
      drawFirstmenu();
    }while(u8g.nextPage() ); 
    //delay(50);
    chng = 0;
    chok = false;
    chup = false;
    chdw = false;
    
    Serial.print("Value of counter is ");
    Serial.println(first_menu_pos);
    
    up_pressed();
    down_pressed();

    if (chdw)
    {
      Serial.print("UP_PRESSED");
      chng = 1;
    }
    else if (chup)
    {
      Serial.print("DOWN_PRESSED");
      chng = -1;
      
    }
    else{
      chng = 0;
    }

    first_menu_pos = first_menu_pos + chng;
    

    if (first_menu_pos >= 3)
    {
      first_menu_pos = 2;
    }

    if ( first_menu_pos<0 )
    {
      first_menu_pos = 0;
    }

    btn_pressed();    
    if (chok)
    {
      Serial.print("Button Pressed inside SS 1");
      //State = 1;
      if (first_menu_pos == 0){
        State = 3;
        //continue;
      }
      if (first_menu_pos == 1){
        State = 4;
        //continue;
      }
      if (first_menu_pos == 2){
        State = 0;
        //continue;
      }

    }

  }

  if (State == 4)
  {
    
    Serial.println(State);
    u8g.firstPage();
    do
    {
      drawFourthmenu();
    }while(u8g.nextPage() ); 

    
  }

  if (State == 3)
  {
    
    Serial.print("Software state :");
    Serial.println(State);
    
    u8g.firstPage();
    do
    {
      drawThirdmenu();
    }while(u8g.nextPage() ); 

    chng = 0;
    chok = false;
    chup = false;
    chdw = false;
    
    Serial.print("Value of counter is ");
    Serial.println(third_menu_pos);
    
   up_pressed();
   down_pressed();

    if (chdw)
    {
      Serial.print("UP_PRESSED");
      chng = 1;
    }
    else if (chup)
    {
      Serial.print("DOWN_PRESSED");
      chng = -1;
      
    }
    else{
      chng = 0;
    }

    third_menu_pos = third_menu_pos + chng;
    

    if (third_menu_pos >= 3)
    {
      third_menu_pos = 2;
    }

    if ( third_menu_pos<0 )
    {
      third_menu_pos = 0;
    }

    btn_pressed();    
    if (chok)
    {
      Serial.print("Button Pressed inside SS 1");
      //State = 1;
      if (third_menu_pos == 0){
        glass_size = 1;
        State = 31;
        //continue;
      }
      if (third_menu_pos == 1){
        glass_size = 2;
        State = 31;
        //continue;
      }
      if (third_menu_pos == 2){
        glass_size = 3;
        State = 31;
        //continue;
      }

    }

    
  }

    if (State == 31)
  {
    
    Serial.print("Software state :");
    Serial.println(State);
    
    u8g.firstPage();
    do
    {
      drawThird1menu();
    }while(u8g.nextPage() ); 

    chng = 0;
    chok = false;
    chup = false;
    chdw = false;
    
    Serial.print("Value of counter is ");
    Serial.println(masala_pos);
    
   up_pressed();
   down_pressed();

    if (chdw)
    {
      Serial.print("UP_PRESSED");
      chng = 1;
    }
    else if (chup)
    {
      Serial.print("DOWN_PRESSED");
      chng = -1;
      
    }
    else{
      chng = 0;
    }

    masala_pos = masala_pos + chng;
    

    if (masala_pos >= 9)
    {
      masala_pos = 9;
    }

    if ( masala_pos<0 )
    {
      masala_pos = 0;
    }

    btn_pressed();    
    if (chok)
    {
      Serial.print("Button Pressed inside SS 1");
      //State = 1;
      if (masala_pos == 0){
        State = 32;
      }
      if (masala_pos == 1){
        State = 32;
        //continue;
      }
      if (masala_pos == 2){
        State = 32;
        //continue;
      }
      if (masala_pos == 3){
        State = 32;
        //continue;
      }
      if (masala_pos == 4){
        State = 32;
        //continue;
      }
      if (masala_pos == 5){
        State = 32;
        //continue;
      }
      if (masala_pos == 6){
        State = 32;
        //continue;
      }
      if (masala_pos == 7){
        State = 32;
        //continue;
      }
      if (masala_pos == 8){
        State = 3;
        //continue;
      }
      if (masala_pos == 9){
        State = 33;
        //continue;
      }

    }

    
  }

  if (State == 32)
  {
    Serial.print("Software state :");
    Serial.println(State);
    
    u8g.firstPage();
    do
    {
      drawThird2menu();
    }while(u8g.nextPage() ); 

    chng = 0;
    chok = false;
    chup = false;
    chdw = false;
    
    Serial.print("Value of counter is ");
    Serial.println(third_sec_pos);
    
   up_pressed();
   down_pressed();

    if (chdw)
    {
      Serial.print("UP_PRESSED");
      chng = 1;
    }
    else if (chup)
    {
      Serial.print("DOWN_PRESSED");
      chng = -1;
      
    }
    else{
      chng = 0;
    }

    third_sec_pos = third_sec_pos + chng;

    if (third_sec_pos > 3){
      third_sec_pos = 3;
    }
    if (third_sec_pos < 0){
      third_sec_pos = 0 ;
    }

    btn_pressed();    
    if (chok)
    {
      Serial.print("Button Pressed");
      //State = 1;
      if (third_sec_pos == 0){
        ar_masala[masala_pos] =third_sec_pos  + 1;
        update_masala();
        State = 31;
        
      }
      if (third_sec_pos == 1){
       
        ar_masala[masala_pos] = third_sec_pos + 1;
        update_masala();
        State = 31;
        //continue;
      }
      if (third_sec_pos == 2){
      
        ar_masala[masala_pos] = third_sec_pos + 1;
         update_masala();
        State = 31;
        //continue;
      }
      if (third_sec_pos == 3){
        ar_masala[masala_pos] = 0;
        update_masala();
        State = 31;
        //continue;
      }
    }

    
    
  }

  if (State == 33){
    Serial.print("Software state :");
    Serial.println(State);
    u8g.firstPage();
    do
    {
      drawThird3menu();
    }while(u8g.nextPage() ); 
    //delay(50);
    chng = 0;
    chok = false;
    chup = false;
    chdw = false;
    
    Serial.print("Value of counter is ");
    Serial.println(third_three_pos);
    
    up_pressed();
    down_pressed();

    if (chdw)
    {
      Serial.print("UP_PRESSED");
      chng = 1;
    }
    else if (chup)
    {
      Serial.print("DOWN_PRESSED");
      chng = -1;
      
    }
    else{
      chng = 0;
    }

    third_three_pos = third_three_pos + chng;
    

    if (third_three_pos >= 3)
    {
      third_three_pos = 2;
    }

    if ( third_three_pos<0 )
    {
      third_three_pos = 0;
    }

    btn_pressed();    
    if (chok)
    {
      Serial.print("Button Pressed");
      //State = 1;
      if (third_three_pos == 0)
      {
        milks =1;
        State = 5;
        //continue;
      }
      if (third_three_pos == 1)
      {
        milks = 0;
        State = 5;
        //continue;
      }

    }
    
  }

  if (State == 5){
   u8g.firstPage();
    do
    {
      drawFifthmenu();
    }while(u8g.nextPage() );  
  }

  
  
  
}
