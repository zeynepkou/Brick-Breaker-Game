#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RED 0xF800 
#define OLED_RESET 0
#define SCREEN_ADDRESS 0x3D
#define SCREEN_WIDTH 128 // Ekranın genişliği
#define SCREEN_HEIGHT 64 // Ekranın yüksekliği

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LDR_PIN A2 // LDR sensörünüzün bağlı olduğu pin
#define POT_PIN A0 // potansiyometreyi bağladım buna
#define BUTTON_UP 12
#define BUTTON_DOWN 11
#define BUTTON_SELECT 10

#define SEG_A 1
#define SEG_B 2
#define SEG_C 3
#define SEG_D 4
#define SEG_E 5
#define SEG_F 6
#define SEG_G 7

int led1=8;
int led2=9;
int led3=13;
int sayac = 0;
int sayac2=0;
int level=0;


int numbers[10][7] = {
  // A, B, C, D, E, F, G
  {1, 1, 1, 1, 1, 1, 0}, //0 
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int menuSelection = 0; 
bool oyun_basladiMi = false; // Oyunun başlayıp başlamadığını kontrol eden değişken
// değişkenlerim
int tahta, topX, topY;
int topDirX = 1, topDirY = -1;
const int tuglaSatir = 4; // Tuğla satırlarının sayısı
const int tuglaSutun = 8; // Tuğla sütunlarının sayısı
const int tuglagenislik = display.width() / tuglaSutun; // Her tuğlanın genişliği
const int tuglayukseklik = 6; // Her tuğlanın yüksekliği
//bool tuglalar[tuglaSatir][tuglaSutun]; // Tuğlaları tutan dizim
// 5 farklı tuğla düzeni tanımlayalım
bool tuglaDuzenleri[5][tuglaSatir][tuglaSutun] = {
  {
     {true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true}

  },
   {
    {true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true},
    {true, true, true, false, false, false, true, true},
    {true, true, false, false, false, false, false, true}
    
    
  },
   {
   {true, true, true, true, true, true, true, true},
    {true, true, true, false, false, true, true, true},
    {true, true, true, false, false, false, true, true},
    {false, false, false, false, false, false, false, false}
  },
   {
    {true, true, false, true, true, false, true, true},
    {true, true, false, true, true, false, true, true},
    {false, false, true, false, false, true, false, false},
    {false, true, false, false, false, false, true, true}
  },
   {
   {false, false, false, true, true, false, false, false},
    {false, true, true, false, true, true, true, false},
    {true, true, false, false, false, false, true, false},
    {true, false, false, false, false, false, false, true}
  },
  
};

bool secilenTuglaDuzeni(bool secilenDuzen[tuglaSatir][tuglaSutun], int level) {
  if (level >= 5) // Örnek olarak 5 seviyeden sonra aynı düzeni tekrar kullanmak yerine ilk seviyeye dönülebilir.
    level = 0;

  for (int i = 0; i < tuglaSatir; i++) {
    for (int j = 0; j < tuglaSutun; j++) {
      secilenDuzen[i][j] = tuglaDuzenleri[level][i][j];
    }
  }
  return secilenDuzen;
}

bool heartFalling = false;
int heartX, heartY;
int heartCounter = 0; // Kalp nesnesi düşürme sayacı

bool tuglalar[tuglaSatir][tuglaSutun];
void setup() {
   display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.clearDisplay();
  // Başlangıç ekranını göster
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Merhaba!");
  display.println("Iyi eglenceler:)");
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  
 
  display.display();
  delay(1000); 
 
   pinMode(LDR_PIN, INPUT); // LDR pinini giriş olarak ayarladık
  secilenTuglaDuzeni(tuglalar,level);
  display.display();
  
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  // tahtamın başlangıç pozisyonu
  tahta = display.width()/2;
  // Topun başlangıç pozisyonu
  topX = display.width() / 2;
  topY = display.height() / 2;

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}
  int kaybetme=0;
  int can = 3; // Oyuncunun can sayısı
  
void loop() {
  display.clearDisplay();
  
  if (!oyun_basladiMi) {
    display.setCursor(0,0);
    display.setTextColor(WHITE, BLACK); 
    display.println("Oyun Menusu");
    
    // Menü öğelerini göster
    if(menuSelection == 0) {
      display.setTextColor(BLACK, WHITE); 
      display.println("1. Baslat");
      display.setTextColor(WHITE, BLACK); 
      display.println("2. Cikis");
    } else {
      display.setTextColor(WHITE, BLACK);
      display.println("1. Baslat");
      display.setTextColor(BLACK, WHITE);
      display.println("2. Cikis");
    }
    
    display.display();
    
    // Menü navigasyonu
    if (digitalRead(BUTTON_UP) == LOW) {
      if(menuSelection > 0) {
        menuSelection--;
      }
      while(digitalRead(BUTTON_UP) == LOW); 
    }
    
    if (digitalRead(BUTTON_DOWN) == LOW) {
      if(menuSelection < 1) { 
        menuSelection++;
      }
      while(digitalRead(BUTTON_DOWN) == LOW); 
    }
    
    if (digitalRead(BUTTON_SELECT) == LOW) {
      executeMenuOption(menuSelection);
      while(digitalRead(BUTTON_SELECT) == LOW); 
    }
  }
  else {
   
  int ldrValue = analogRead(LDR_PIN); // LDR değerini okur
  bool shouldInvert = ldrValue > 512; // Eşik değeri, ortam ışığınıza göre ayarlayın
  tahta = map(analogRead(POT_PIN), 0, 1023, 0, display.width() - 20); // Potansiyometre değerini oku ve tahta pozisyonunu güncelle

  // Tahtayı çizme kısmı
  display.fillRect(tahta, display.height() - 5, 20, 5, WHITE);

  // Topu çizme kısmı
  display.fillCircle(topX, topY, 2, WHITE);

  // Tuğlaları çizme kısmı
  for (int i = 0; i < tuglaSatir; i++) {
    for (int j = 0; j < tuglaSutun; j++) {
      if (tuglalar[i][j]) {
        display.fillRect(j * tuglagenislik, i * tuglayukseklik, tuglagenislik - 1, tuglayukseklik - 1, WHITE);
      }
    }
  }

  // Topun hareketini güncellediğimiz yer
  topX += topDirX;
  topY += topDirY;
 
  // Top sınırlara çarparsa yönünü değiştir
  if (topX <= 0 || topX >= display.width()) topDirX *= -1;
  if (topY <= 0) topDirY *= -1;

  // Eğer top tahtaya çarparsa yönünü değiştir
  if (topY >= display.height() - 10 && topX >= tahta && topX <= tahta + 20) topDirY *= -1;

int toplamTugla = 0;
for (int i = 0; i < tuglaSatir; i++) {
  for (int j = 0; j < tuglaSutun; j++) {
    if (tuglalar[i][j]) {
      toplamTugla++;
    }
  }
}

  for (int i = 0; i < tuglaSatir; i++) {
  for (int j = 0; j < tuglaSutun; j++) {
    if (tuglalar[i][j]) {
      if (topX > j * tuglagenislik && topX < (j + 1) * tuglagenislik &&
          topY > i * tuglayukseklik && topY < (i + 1) * tuglayukseklik) {
        tuglalar[i][j] = false; // Tuğlayı kır
        topDirY *= -1; // Topun yönünü değiştir
        sayac++; // Tuğla sayacını artır
        sayac2++;
        
        if (sayac > 9) {
          sayac = 0; // Sayacı sıfırla
        }
        display.setCursor(0, display.height() - 10); // Skoru ekranın en altında en sol köşeye yerleştir
        display.setTextColor(WHITE, BLACK);
        display.print("Skor:");
        display.println(sayac2);
        // Ekranı güncelle
        display.display();
        displayNumber(sayac); // Sayacı seven segment display'de göster

        // Kalp nesnesi düşürme kısmı
        heartCounter++;
        if(toplamTugla<=19)
        {
        if (heartCounter >= 11) { 
          heartCounter = 0; 
          heartFalling = true; // Kalp nesnesini düşür
          heartX = j * tuglagenislik + tuglagenislik / 2; // Kalp nesnesinin başlangıç X koordinatı
          heartY = i * tuglayukseklik; // Kalp nesnesinin başlangıç Y koordinatı
          
        }
        }
         if(toplamTugla>19&&toplamTugla<=29)
        {
        if (heartCounter >= 14) { 
          heartCounter = 0; // Sayacı sıfırla
          heartFalling = true; // Kalp nesnesini düşür
          heartX = j * tuglagenislik + tuglagenislik / 2; // Kalp nesnesinin başlangıç X koordinatı
          heartY = i * tuglayukseklik; // Kalp nesnesinin başlangıç Y koordinatı
          
        }
        }
         if(toplamTugla>29&&toplamTugla<=39)
        {
        if (heartCounter >= 13) {
          heartCounter = 0; // Sayacı sıfırla
          heartFalling = true; // Kalp nesnesini düşür
          heartX = j * tuglagenislik + tuglagenislik / 2; // Kalp nesnesinin başlangıç X koordinatı
          heartY = i * tuglayukseklik; // Kalp nesnesinin başlangıç Y koordinatı
          
        }
        }
      }
    }
  }
}

  if (topY > display.height()) {
   
    if (can == 3) {
      digitalWrite(led3, LOW);
    } else if (can == 2) {
      digitalWrite(led2, LOW);
    } else if (can == 1) {
      digitalWrite(led1, LOW);
    }
     resetGame();
  }
// Tüm tuğlalar kırıldı mı kontrol et
    bool allBricksBroken = true;
    for (int i = 0; i < tuglaSatir; i++) {
      for (int j = 0; j < tuglaSutun; j++) {
        if (tuglalar[i][j]) {
          allBricksBroken = false;
          break;
        }
      }
      if (!allBricksBroken) {
        break;
      }
    }

    if (allBricksBroken) {
      // Tüm tuğlalar kırıldı, bir sonraki seviyeye geç
      nextLevel();
}

  if (shouldInvert) {
    display.invertDisplay(true); // Eğer eşik değerinden yüksekse ekranı ters çevir
  } else {
    display.invertDisplay(false); // Değilse normal görüntüle
  }
// Kalp nesnesinin düşme mantığı
    if (heartFalling) {
      heartY++; // Kalp nesnesinin Y koordinatını artırarak aşağı doğru hareket ettir

      // Kalp nesnesini OLED ekranda çiz
      drawHeart(heartX, heartY); // Yeni konumda kalp çiz

      // Kalp ekranın altına düştüyse veya platform tarafından yakalandıysa
      if (heartY > display.height() || (heartY >= display.height() - 10 && heartX >= tahta && heartX <= tahta + 20)) {
        heartFalling = false; // Kalp düşme durumunu sonlandır
        if (heartY <= display.height()) {
         
          if(can<3)
          {
             can++; // Eğer platform tarafından yakalandıysa can sayısını artır
             if(can==3)
             {
              digitalWrite(led1, HIGH);
              digitalWrite(led2, HIGH);
              digitalWrite(led3, HIGH);
             }
             else if(can==2)
             {
              digitalWrite(led2,HIGH);
             }
          }
        }
      }
    }
  // Ekranı güncelle
  display.display();

  delay(10); // Hareket hızını kontrol etmek için
  }
}
void drawHeart(int x, int y) {
  // Kalp şeklinin üst kısmını oluşturan iki daire çiz
  display.fillCircle(x, y, 3, WHITE); // Sol daire
  display.fillCircle(x + 6, y, 3, WHITE); // Sağ daire

  // Kalp şeklinin alt kısmını oluşturan üçgeni çiz
  display.fillTriangle(x - 3, y, x + 9, y, x + 3, y + 7, WHITE);
}
void executeMenuOption(int option) {
  switch (option) {
    case 0:
      // "Başlat" seçeneği için kodlar
      if(can > 0) { // Eğer can sayısı 0'dan büyükse başlatma işlemlerini yap
        oyun_basladiMi = true; // Oyunun başladığını belirten değişkeni true yap
        
        topX = display.width() / 2;
        topY = display.height() / 2;
        topDirX = 1;
        topDirY = -1;
        displayNumber(0); 
        secilenTuglaDuzeni(tuglalar,level); // Rastgele bir tuğla düzeni seç
      } else { 
        display.clearDisplay();
        display.setCursor(0,0);
        display.setTextColor(WHITE, BLACK); 
        display.println("Can sayisi yetersiz!");
        
        display.display();
        delay(2000); 
      }
      break;
    case 1:
      // "Çıkış" seçeneği için kodlar
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextColor(WHITE, BLACK); 
      display.println("Oyunumuza\ngosterdiginiz ilgi\nicin tesekkurler");
      display.display();
      delay(2000); 
      oyun_basladiMi = false; 
      sayac = 0;
      displayNumber(sayac); // Sayacı seven segment display'de göster
      loop();
      break;
  }
}

void resetGame() {
  can--; 

  if (can == 0) { // Eğer can sıfırsa oyunu tamamen sıfırla
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(WHITE, BLACK); 
    
    display.println("Bitti");
   
    display.print("Skor:");
display.print(sayac2);

    can=3;
    display.display();
    delay(2000); 
    oyun_basladiMi = false;
    sayac = 0;
    displayNumber(sayac); // Sayacı seven segment display'de göster
     level = 0;
     sayac2=0;
    secilenTuglaDuzeni(tuglalar, level);
    digitalWrite(led1, HIGH); // Tüm LED'leri kapat
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
   
  } else { // Eğer can varsa devam et
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(WHITE, BLACK); 
    display.println("Can kaybettiniz");
    display.display();
    delay(1000); 
    oyun_basladiMi = true; // Oyunun başladığını belirten değişkeni true yap
    // Topu tahtanın üst kısmına yerleştir
    topX = tahta + 10; // Tahtanın orta noktası
    topY = display.height() -15; // Tahtanın üst kısmı
    
    delay(2000); 
  }

 // loop();
  
}
void nextLevel() {
  // Seviye tamamlandı mesajını göster
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE, BLACK);
  display.print("Skor:");
  display.println(sayac2);
  display.print(level+1);
  display.println(". Seviye Tamamlandi!");
  display.display();
  delay(1000);

  // Seviye arttır ve gerekli diğer işlemleri yap
  level++;

  // Yeni seviyeyi başlatmak için kısa bir bekleme yapın
  delay(2000);

  topX = display.width() / 2;
  topY = display.height() / 2;
  // Topun hızını yüzde 20 artır
  topDirX *= 1.2;
  topDirY *= 1.2;

  // Seviyeye özgü tuğla düzenini seç
  secilenTuglaDuzeni(tuglalar, level);

  // Oyunun başladığını işaretle
  oyun_basladiMi = true;
}

// Seven segment display'de sayı gösterme fonksiyonu
void displayNumber(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(i + SEG_A, numbers[num][i]);
  }
}
