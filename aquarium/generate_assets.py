import os
from PIL import Image, ImageDraw

def create_assets():
    # 1. Créer le dossier assets s'il n'existe pas
    if not os.path.exists("assets"):
        os.makedirs("assets")
        print("Dossier 'assets' créé.")

    # --- IMAGE 1 : LE POISSON (fish.bmp) ---
    # Fond transparent (ou magenta pour la transparence simple), ici noir pour simplifier
    img_fish = Image.new("RGB", (64, 64), (20, 30, 60)) # Fond couleur eau
    draw = ImageDraw.Draw(img_fish)
    # Corps orange
    draw.ellipse([10, 15, 50, 49], fill=(255, 140, 0), outline=(255, 255, 255))
    # Queue
    draw.polygon([(10, 32), (0, 15), (0, 49)], fill=(255, 140, 0))
    # Oeil
    draw.ellipse([35, 25, 40, 30], fill=(255, 255, 255))
    draw.ellipse([38, 27, 39, 28], fill=(0, 0, 0))
    
    img_fish.save("assets/fish.bmp")
    print("-> assets/fish.bmp généré.")

    # --- IMAGE 2 : L'ALGUE (algae.bmp) ---
    img_algae = Image.new("RGB", (64, 64), (20, 30, 60)) # Fond couleur eau
    draw = ImageDraw.Draw(img_algae)
    # Tiges vertes
    draw.line([(32, 64), (32, 20)], fill=(0, 255, 0), width=3)
    draw.line([(32, 64), (20, 30)], fill=(0, 200, 0), width=3)
    draw.line([(32, 64), (44, 25)], fill=(50, 255, 50), width=3)
    
    img_algae.save("assets/algae.bmp")
    print("-> assets/algae.bmp généré.")

    # --- IMAGE 3 : FOND (background.bmp) ---
    # Juste un carré bleu océan
    img_bg = Image.new("RGB", (200, 200), (20, 30, 60))
    img_bg.save("assets/background.bmp")
    print("-> assets/background.bmp généré.")

if __name__ == "__main__":
    try:
        create_assets()
        print("Tout est prêt ! Tu peux lancer ton programme C++.")
    except ImportError:
        print("Erreur : La librairie Pillow n'est pas installée.")
        print("Fais 'pip install pillow' dans ton terminal.")