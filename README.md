# **Tuğla Kırma Oyunu**

Bu proje, **Arduino ve OLED ekran** kullanarak geliştirilmiş bir **tuğla kırma oyunudur**. Oyunda **potansiyometre ile kontrol edilen bir tahta**, **hareket eden bir top** ve **kırılabilecek tuğla dizilimleri** bulunmaktadır. **LDR sensörü ile ortam ışığına göre ekran ters dönme efekti eklenmiştir.** Ayrıca oyun **kademeli olarak zorlaşmaktadır** ve **can sistemi** bulunmaktadır.

---

## **Özellikler**  

- **Potansiyometre ile tahta kontrolü**  
- **Otomatik hareket eden top mekaniği**  
- **Farklı seviyelerde tuğla dizilimleri**  
- **LDR sensörü ile ortam ışığı algılama ve ekran ters dönme efekti**  
- **Seviyeler ilerledikçe topun hızını arttırma**  
- **Kalp mekanizması ile can kazanma**  
- **Seven Segment Display ile skor görüntüleme**  

---

## **Donanım Gereksinimleri**

Bu projeyi gerçekleştirmek için aşağıdaki bileşenlere ihtiyacınız vardır:

- **Arduino (Uno, Mega, vs.)**
- **128x64 OLED ekran (SSD1306)**
- **Potansiyometre**
- **LDR (Işık Sensörü)**
- **3 Adet LED** (Can durumu görseli için)
- **3 Buton (Yukari, Aşağı, Seçim)**
- **7 Segment Display**
- **Bağlantı kabloları**

---

## **Kurulum ve Kullanım**

### **1. Projeyi Klonlayın**  

Aşağıdaki komutu terminal veya komut istemcisine girerek projeyi klonlayın:  

```sh
git clone https://github.com/Zeynepkou/Brick-Breaker-Game.git
cd Brick-Breaker-Game
```

### **2. Bağlantılar**

Aşağıda **Arduino ile bileşenler arasındaki bağlantılar** verilmiştir:

- **OLED Ekran**
  - VCC → 5V
  - GND → GND
  - SDA → A4 (Arduino Uno için)
  - SCL → A5 (Arduino Uno için)
- **LDR Sensörü** → A2
- **Potansiyometre** → A0
- **LED Bağlantıları**
  - LED1 → 8
  - LED2 → 9
  - LED3 → 13
- **Butonlar**
  - Yukarı → 12
  - Aşağı → 11
  - Seçim → 10
- **7 Segment Display**
  - Segment A → 1
  - Segment B → 2
  - Segment C → 3
  - Segment D → 4
  - Segment E → 5
  - Segment F → 6
  - Segment G → 7

### **3. Kodun Yüklenmesi**

Arduino IDE veya PlatformIO kullanarak aşağıdaki adımları takip ederek projeyi yükleyebilirsiniz:

1. **Gerekli kütüphaneleri yükleyin:**  
   - `Adafruit_GFX`  
   - `Adafruit_SSD1306`
2. **Kodu Arduino'ya yükleyin.**
3. **Bağlantıları kontrol edin ve Arduino'yu bağlayın.**
4. **Arduino IDE'de uygun port ve kartı seçin.**
5. **Kodu derleyip yükleyin.**

---

## **Oyun Mekaniği**

- **Oyuna Başlama:**
  - "**1. Başlat**" ve "**2. Çıkış**" seçenekleri mevcuttur.
  - "Başlat" seçildiğinde top harekete geçer.
  
- **Tahta Kontrolü:**
  - Potansiyometre ile sola-sağa hareket ettirilir.
  
- **Topun Hareketi:**
  - Top ekranın sınırlarına çarptığında geri sekerek hareket eder.
  - Tuğla dizilimlerine çarptığında tuğla kırılır ve skor artar.
  
- **Seviyeler ve Skor:**
  - Toplamda 5 farklı tuğla dizilimi vardır.
  - Her seviyede tuğla düzeni değişir.
  - Tüm tuğlalar kırılırsa **bir sonraki seviyeye geçilir** ve top hızlanır.
  
- **Can Sistemi ve Kalpler:**
  - Oyuncunun **başlangıçta 3 canı vardır.**
  - **LED'ler can durumunu gösterir.**
  - **Kalp nesneleri rastgele düşer**, yakalanırsa **ekstra can kazanılır**.
  - **Canlar biterse oyun sona erer.**
  
- **Oyun Bitişi:**
  - Tüm canlar tükenirse oyun sona erer ve **skor ekranda gösterilir.**
  - "**Oyun Bitti!**" mesajı gösterilir ve menüye dönülür.

---

## **Görsel**

![Video Önizleme](https://github.com/zeynepkou/Brick-Breaker-Game/blob/31482c2a266ee0df9fc7748955ba89d811f0eb65/Brick-Breaker-Game.png)

---

## **Oyun Videosu** 
![Video Önizleme](https://github.com/zeynepkou/Brick-Breaker-Game/blob/b59500f89bb092365b36071b8c08e8dd2e7a4694/Brick-Breaker-Game.gif)

---

**Keyifli oyunlar! 🎉**

