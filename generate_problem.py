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
    model = genai.GenerativeModel('gemini-2.5-flash') # En yaratıcı model
    
    # 2. Kural (Yaratıcı ve Uzun): Prompt'u bu yönde eğitiyoruz
    # 3. Kural (Yorumsuz C): Prompt'ta bunu net olarak belirtiyoruz
    
    # Hikaye için rastgele bir tema seçelim (Stealth kuralı için)
    themes = ["uzay macerası", "antik bir hazine avı", "siber güvenlik senaryosu", "bir restoran yönetimi simülasyonu", "bilimsel bir deney", "gizemli bir adada hayatta kalma","Erzurum","Yazılım Öğrencisi","Bakkal","Yakuphan'ın Maceraları"]
    
    prompt = f"""
    Sen, C programlama dili için ileri düzeyde hikayeli (story-based) sorular yazan bir eğitmensin. 
    Bugünkü tema: "{random.choice(themes)}".

    Lütfen aşağıdaki kurallara göre bir C programlama problemi oluştur:
    
    1. Problem, bu temayı içeren uzun ve yaratıcı bir hikayeye sahip olmalı (Hem EN hem TR için en az 3 paragraf).
    2. Problem; pointer'lar, struct'lar, dinamik bellek yönetimi (malloc/free) veya dosya işlemleri (file I/O) gibi ileri düzey bir C konusunu içermelidir.
    3. Sorunun hem İngilizce (EN) hem de Türkçe (TR) açıklamasını sağlamalısın.
    4. Sorunun tam C çözümünü sağlamalısın.
    
    KURALLAR:
    - **YORUMSUZ KOD:** 'c_solution' içindeki C kodu ASLA ve ASLA yorum satırı (ne // ne de /* */) içermemelidir.
    - **FORMAT:** Cevabın SADECE aşağıdakine benzer bir JSON formatında olmalıdır:

    {{
      "problem_slug": "kisa_problem_adi_snake_case",
      "en_description": "Very long story-based problem description in English...",
      "tr_description": "Çok uzun hikayeli problem açıklaması Türkçe olarak...",
      "c_solution": "#include <stdio.h>\n#include <stdlib.h>\n\nint main() {{\n    // ...çözüm kodu...\n    return 0;\n}}"
    }}
    """
    
    response_text_for_logging = "API çağrısı başarısız oldu, response yok." # Hata durumunda loglanacak varsayılan mesaj
    try:
        response = model.generate_content(prompt)
        response_text_for_logging = response.text # Başarılıysa cevabı al
        
        # Gemini'nin cevabındaki ```json ... ``` kısımlarını temizle
        cleaned_json = re.sub(r"```json\n(.*?)\n```", r"\1", response_text_for_logging, flags=re.DOTALL)
        return json.loads(cleaned_json)
    except Exception as e:
        print(f"Gemini API Hatası: {e}")
        print(f"Alınan Ham Cevap (veya hata): {response_text_for_logging}") # Artık UnboundLocalError vermeyecek
        return None

def strip_comments(code):
    """C kodundaki tüm yorum satırlarını (// ve /*...*/) temizler."""
    code = re.sub(r"//.*", "", code) # Tek satırlı yorumları kaldır
    code = re.sub(r"/\*[\s\S]*?\*/", "", code) # Çok satırlı yorumları kaldır
    return code

def create_problem_files(content, next_num):
    """Gelen içeriğe göre klasör ve dosyaları oluşturur."""
    
    slug = content['problem_slug']
    folder_name = f"{next_num:02d}_{slug}" # Örn: 11_space_pirate_loot
    c_file_name = f"{folder_name}.c"
    
    # 1. Klasör oluştur
    os.makedirs(folder_name, exist_ok=True)
    
    # 2. description.txt oluştur
    desc_content = f"EN\n\n{content['en_description']}\n\nTR\n\n{content['tr_description']}"
    with open(os.path.join(folder_name, "description.txt"), "w", encoding="utf-8") as f:
        f.write(desc_content)
        
    # 3. .c çözüm dosyasını oluştur (3. Kural: Yorumsuz)
    # Gemini'ye güvensek de, garantilemek için yorumları tekrar temizliyoruz.
    code_no_comments = strip_comments(content['c_solution'])
    
    with open(os.path.join(folder_name, c_file_name), "w", encoding="utf-8") as f:
        f.write(code_no_comments)
        
    print(f"Başarıyla oluşturuldu: {folder_name}")
    return folder_name

def create_commit_message(folder_name, slug):
    """1. Kural (Stealth): İnsan gibi görünen rastgele bir commit mesajı oluşturur."""
    
    messages = [
        f"Add new problem: {slug}",
        f"Create solution for {folder_name}",
        f"Add exercise {folder_name.split('_')[0]}",
        f"Yeni C alıştırması eklendi: {slug}",
        f"Add {slug} challenge"
    ]
    
    message = random.choice(messages)
    
    # Mesajı, betiğin çalıştığı mevcut dizine (public repo'nun kök dizini olacak) yaz.
    with open("commit_message.txt", "w", encoding="utf-8") as f:
        f.write(message)

def main():
    api_key = os.environ.get("GEMINI_API_KEY")
    if not api_key:
        raise ValueError("GEMINI_API_KEY bulunamadı!")
        
    next_num = get_next_problem_number()
    print(f"Sıradaki problem numarası: {next_num}")
    
    content = generate_problem_content(api_key)
    
    if content:
        folder_name = create_problem_files(content, next_num)
        create_commit_message(folder_name, content['problem_slug'])
    else:
        raise Exception("Gemini'den geçerli içerik alınamadı.")

if __name__ == "__main__":
    main()
