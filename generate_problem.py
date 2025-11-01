import os
import google.generativeai as genai
import json
import re
import glob
import random

def get_next_problem_number():
    """Repodaki en son problem numarasını bulur ve bir sonrakini döndürür."""
    # Sadece 01_... 02_... formatındaki klasörleri listele
    folders = [f for f in glob.glob("[0-9][0-9]_*") if os.path.isdir(f)]
    
    if not folders:
        return 1
        
    last_num = 0
    for folder_name in folders:
        try:
            num = int(folder_name.split('_')[0])
            if num > last_num:
                last_num = num
        except ValueError:
            continue
            
    return last_num + 1

def generate_problem_content(api_key):
    """Gemini API'yi kullanarak yeni bir problem ve çözüm üretir."""
    genai.configure(api_key=api_key)
    # 'latest' etiketini kaldırdık, stabil modeli (gemini-1.5-pro) kullanıyoruz
    model = genai.GenerativeModel('gemini-2.5-flash')
    
    # 1. YENİ İSTEK: Zorluk seviyesini rastgele seç
    difficulty = random.choice(["EASY", "MEDIUM", "HARD"])
    
    # 2. YENİ İSTEK: Zorluk seviyesine göre prompt'u (komutu) belirle
    
    if difficulty == "EASY":
        prompt = """
        Sen, C programlama dili için "EASY" (Kolay) seviyede sorular yazan bir eğitmensin.
        
        KURALLAR:
        1. Soru, "loops" (döngüler), "arrays" (diziler), temel matematiksel operatörler veya "if/else" şartları gibi temel C konularını içermelidir.
        2. Soru HİKAYELİ OLMASIN. Doğrudan bir problem tanımı olsun. (Örn: "Bir dizideki en büyük sayıyı bulan...").
        3. Açıklama (EN ve TR) kısa ve net olmalı (1-2 paragraf yeterli).
        4. Problem ASLA "pointer" (işaretçi), "struct", "typedef" veya "dosya işlemleri" (file I/O) içermemelidir.
        5. Çözüm kodu (c_solution) ASLA yorum satırı (// veya /* */) içermemelidir.

        İSTENEN JSON FORMATI:
        {
          "problem_slug": "kisa_ingilizce_baslik_snake_case",
          "difficulty": "EASY",
          "en_description": "Short and direct 'Easy' problem description in English.",
          "tr_description": "Kısa ve doğrudan 'Kolay' problem açıklaması Türkçe olarak.",
          "c_solution": "#include <stdio.h>\n\nint main() {\n    // Kolay seviye çözüm kodu...\n    return 0;\n}"
        }
        """
    elif difficulty == "MEDIUM":
        prompt = """
        Sen, C programlama dili için "MEDIUM" (Orta) seviyede sorular yazan bir eğitmensin.
        
        KURALLAR:
        1. Soru, "struct", "typedef" KULLANIMINI veya "dosya işlemleri" (file I/O - fopen, fwrite, fread, fclose) konusunu içermelidir.
        2. Alternatif olarak, "struct" veya "dosya" içermiyorsa, mantıksal olarak zorlayıcı bir algoritma problemi olmalıdır (örn: sıralama, arama, matris işlemleri).
        3. Problem ASLA "pointer" (işaretçi) veya "dinamik bellek" (malloc/free) içermemelidir. (struct içinde pointer olmadan kullanılabilir).
        4. Açıklama (EN ve TR) orta uzunlukta ve net olmalı (2-3 paragraf).
        5. Çözüm kodu (c_solution) ASLA yorum satırı (// veya /* */) içermemelidir.

        İSTENEN JSON FORMATI:
        {
          "problem_slug": "medium_english_slug_snake_case",
          "difficulty": "MEDIUM",
          "en_description": "Medium-length, clear problem description (e.g., using structs or file I/O).",
          "tr_description": "Orta uzunlukta, net problem açıklaması (örn: struct veya dosya işlemleri kullanarak).",
          "c_solution": "#include <stdio.h>\n#include <stdlib.h>\n\ntypedef struct {\n // ... \n} Student;\n\nint main() {\n    // Orta seviye çözüm kodu...\n    return 0;\n}"
        }
        """
    else: # difficulty == "HARD"
        prompt = """
        Sen, C programlama dili için "HARD" (Zor) seviyede sorular yazan bir eğitmensin.
        
        KURALLAR:
        1. Soru ZORUNLU olarak "pointer" (işaretçi) ve "dinamik bellek yönetimi" (malloc, free, realloc) konularını içermelidir.
        2. Soru "pointer to pointer" (işaretçinin işaretçisi), "linked lists" (bağlı listeler) veya "dinamik diziler" gibi karmaşık konulara odaklanmalıdır.
        3. Problem ASLA "struct", "typedef" veya "dosya işlemleri" (file I/O) içermemelidir. (İsteğiniz üzerine bu konular MEDIUM'da kaldı).
        4. Açıklama (EN ve TR) zor problemi detaylıca anlatacak şekilde uzun ve net olmalı (3+ paragraf).
        5. Çözüm kodu (c_solution) ASLA yorum satırı (// veya /* */) içermemelidir.

        İSTENEN JSON FORMATI:
        {
          "problem_slug": "hard_pointer_problem_slug_snake_case",
          "difficulty": "HARD",
          "en_description": "Detailed 'Hard' problem description focusing on pointers and dynamic memory.",
          "tr_description": "İşaretçiler ve dinamik bellek odaklı, detaylı 'Zor' problem açıklaması.",
          "c_solution": "#include <stdio.h>\n#include <stdlib.h>\n\nint main() {\n    int **matrix = (int **)malloc(5 * sizeof(int *));\n    // ... Zor seviye çözüm kodu ...\n    free(matrix);\n    return 0;\n}"
        }
        """

    response_text_for_logging = "API çağrısı başarısız oldu, response yok."
    try:
        response = model.generate_content(prompt)
        response_text_for_logging = response.text
        
        # Gemini'nin cevabındaki ```json ... ``` kısımlarını temizle
        cleaned_json = re.sub(r"```json\n(.*?)\n```", r"\1", response_text_for_logging, flags=re.DOTALL)
        return json.loads(cleaned_json)
    except Exception as e:
        print(f"Gemini API Hatası: {e}")
        print(f"Alınan Ham Cevap (veya hata): {response_text_for_logging}")
        return None

def strip_comments(code):
    """C kodundaki tüm yorum satırlarını (// ve /*...*/) temizler."""
    code = re.sub(r"//.*", "", code) # Tek satırlı yorumları kaldır
    code = re.sub(r"/\*[\s\S]*?\*/", "", code) # Çok satırlı yorumları kaldır
    # Boş satırları da temizleyerek kodu sıkıştıralım
    code = "\n".join([line for line in code.split('\n') if line.strip()])
    return code

def create_problem_files(content, next_num):
    """Gelen içeriğe göre klasör ve dosyaları oluşturur."""
    
    slug = content['problem_slug']
    difficulty = content['difficulty'].upper() # EASY, MEDIUM, HARD
    
    # 3. YENİ İSTEK: Klasör adını zorluk seviyesine göre güncelle
    folder_name = f"{next_num:02d}_{difficulty}_{slug}" # Örn: 11_EASY_find_max_number
    
    c_file_name = f"{folder_name}.c" # Örn: 11_EASY_find_max_number.c
    
    # 1. Klasör oluştur
    os.makedirs(folder_name, exist_ok=True)
    
    # 2. description.txt oluştur
    desc_content = f"EN\n\n{content['en_description']}\n\nTR\n\n{content['tr_description']}"
    with open(os.path.join(folder_name, "description.txt"), "w", encoding="utf-8") as f:
        f.write(desc_content)
        
    # 3. .c çözüm dosyasını oluştur (Yorumsuz)
    code_no_comments = strip_comments(content['c_solution'])
    
    with open(os.path.join(folder_name, c_file_name), "w", encoding="utf-8") as f:
        f.write(code_no_comments)
        
    print(f"Başarıyla oluşturuldu: {folder_name}")
    return folder_name

def create_commit_message(folder_name, slug):
    """1. Kural (Stealth): İnsan gibi görünen rastgele bir commit mesajı oluşturur."""
    
    # Zorluk seviyesini de mesajlara dahil edebiliriz
    difficulty = ""
    try:
        difficulty = folder_name.split('_')[1] # 11_EASY_slug -> EASY
    except:
        pass # Hata olursa boş kalsın
        
    messages = [
        f"Add {difficulty} problem: {slug}",
        f"Create solution for {folder_name}",
        f"Add exercise {folder_name.split('_')[0]} ({difficulty})",
        f"Yeni C alıştırması ({difficulty}) eklendi: {slug}",
        f"Add {slug} challenge"
    ]
    
    message = random.choice(messages)
    
    # Mesajı, workflow'un okuması için (public_repo'nun kök dizinine) yaz
    with open("commit_message.txt", "w", encoding="utf-8") as f:
        f.write(message)

def main():
    api_key = os.environ.get("GEMINI_API_KEY")
    if not api_key:
        raise ValueError("GEMINI_API_KEY bulunamadı!")
        
    # Bu betik public_repo'nun içinde çalıştırıldığı için,
    # mevcut dizindeki ('.') dosyaları kontrol etmesi doğrudur.
    next_num = get_next_problem_number()
    print(f"Sıradaki problem numarası: {next_num}")
    
    content = generate_problem_content(api_key)
    
    if content:
        # Slug'ı da content içinden alıyoruz
        folder_name = create_problem_files(content, next_num)
        create_commit_message(folder_name, content['problem_slug'])
    else:
        raise Exception("Gemini'den geçerli içerik alınamadı.")

if __name__ == "__main__":
    main()
