[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BH1750FVI

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bh1750fvi/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

BH1750FVI ist ein digitaler Umgebungslichtsensor-IC für die I2C-Busschnittstelle. Dieser IC ist am besten geeignet, um die Umgebungslichtdaten zum Anpassen der LCD- und Tastatur-Hintergrundbeleuchtungsleistung des Mobiltelefons zu erhalten. Es ist möglich, einen großen Bereich bei hoher Auflösung zu erkennen. Es kann in Mobiltelefonen, LCD-Fernsehern, HINWEIS-PCs, tragbaren Spielgeräten, Digitalkameras, digitalen Videokameras, PDAs, LCD-Displays usw. verwendet werden.

LibDriver BH1750FVI ist der voll funktionsfähige Treiber von BH1750FVI, der von LibDriver gestartet wurde. Er bietet Helligkeitsmessung im kontinuierlichen Modus, Helligkeitsmessung im Einzelmodus und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver BH1750FVI-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver BH1750FVI IIC.

/test enthält den Testcode des LibDriver BH1750FVI-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver BH1750FVI-Beispielcode.

/doc enthält das LibDriver BH1750FVI-Offlinedokument.

/Datenblatt enthält BH1750FVI-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_bh1750fvi_basic.h"

uint8_t res;
uint32_t i, times;
bh1750fvi_address_t address;

/* set hardware params */
times = 3;
address = BH1750FVI_ADDRESS_LOW;

...
    
/* basic init */
res = bh1750fvi_basic_init(address);
if (res != 0)
{
    return 1;
}

/* delay 1000ms */
bh1750fvi_interface_delay_ms(1000);

...
    
for (i = 0; i < times; i++)
{
    float lux;

    /* basic read */
    res = bh1750fvi_basic_read(&lux);
    if (res != 0)
    {
        (void)bh1750fvi_basic_deinit();
        
        return 1;
    }

    /* output */
    bh1750fvi_interface_debug_print("%d/%d.\n", i + 1, times);
    bh1750fvi_interface_debug_print("%.2flux.\n", lux);

    /* delay 1000ms */
    bh1750fvi_interface_delay_ms(1000);
    
    ...
}

...
    
(void)bh1750fvi_basic_deinit();

return 0;
```
#### example shot

```C
#include "driver_bh1750fvi_shot.h"

uint8_t res;
uint32_t i, times;
bh1750fvi_address_t address;

/* set hardware params */
times = 3;
address = BH1750FVI_ADDRESS_LOW;

...
    
/* shot init */
res = bh1750fvi_shot_init(address);
if (res != 0)
{
    return 1;
}

...
    
for (i = 0; i < times; i++)
{
    float lux;

    /* shot read */
    res = bh1750fvi_shot_read(&lux);
    if (res != 0)
    {
        (void)bh1750fvi_shot_deinit();
        
        return 1;
    }

    /* output */
    bh1750fvi_interface_debug_print("%d/%d.\n", i + 1, times);
    bh1750fvi_interface_debug_print("%.2flux.\n", lux);

    /* delay 1000ms */
    bh1750fvi_interface_delay_ms(1000);
    
    ...
}

...
    
(void)bh1750fvi_shot_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/bh1750fvi/index.html](https://www.libdriver.com/docs/bh1750fvi/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.