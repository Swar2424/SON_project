import tkinter as tk
from pydub import AudioSegment
from pydub.playback import play
from threading import Timer
import customtkinter as ctk
from PIL import Image,ImageTk

ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")





#############################################
#                                           #
#                                           #
#            Définition des                 #
#            Dictionnaires                  #
#                                           #
#                                           #
#                                           #
#############################################







dico1 = {"Percussion" : ["./Mode_1/1_BigKick.wav", 
                         "./Mode_1/1_Kick.wav",
                         "./Mode_1/1_Kick_CT.wav",
                         "./Mode_1/1_Bongos.wav", 
                         "./Mode_1/1_Perc.wav",
                         "./Mode_1/1_Clap.wav", 
                         "./Mode_1/1_OpenHH.wav",
                         "./Mode_1/1_FastCloseHH.wav", 
                         "./Mode_1/1_SlowCloseHH.wav",
                         "./Mode_1/1_Tambourine.wav"],
        
        "Basse T" :["./Mode_1/2_Bass_Si_Aigu_T.wav", 
                    "./Mode_1/2_Bass_La_Aigu_T.wav", 
                    "./Mode_1/2_Bass_Fa_Aigu_T.wav", 
                    "./Mode_1/2_Bass_Mi_Aigu_T.wav", 
                    "./Mode_1/2_Bass_Re_Aigu_T.wav",
                    "./Mode_1/2_Bass_Si_Grave_T.wav", 
                    "./Mode_1/2_Bass_La_Grave_T.wav", 
                    "./Mode_1/2_Bass_Fa_Grave_T.wav", 
                    "./Mode_1/2_Bass_Mi_Grave_T.wav", 
                    "./Mode_1/2_Bass_Re_Grave_T.wav"],     
        
        "Basse CT" :   ["./Mode_1/3_Bass_Si_Aigu_CT.wav", 
                        "./Mode_1/3_Bass_La_Aigu_CT.wav", 
                        "./Mode_1/3_Bass_Fa_Aigu_CT.wav",
                        "./Mode_1/3_Bass_Mi_Aigu_CT.wav", 
                        "./Mode_1/3_Bass_Re_Aigu_CT.wav",
                        "./Mode_1/3_Bass_Si_Grave_CT.wav", 
                        "./Mode_1/3_Bass_La_Grave_CT.wav", 
                        "./Mode_1/3_Bass_Fa_Grave_CT.wav", 
                        "./Mode_1/3_Bass_Mi_Grave_CT.wav", 
                        "./Mode_1/3_Bass_Re_Grave_CT.wav"],
        
        "Synthé T" :   ["./Mode_1/4_Synth_Si_Aigu_T.wav", 
                        "./Mode_1/4_Synth_La_Aigu_T.wav", 
                        "./Mode_1/4_Synth_Fa_Aigu_T.wav", 
                        "./Mode_1/4_Synth_Mi_Aigu_T.wav", 
                        "./Mode_1/4_Synth_Re_Aigu_T.wav",
                        "./Mode_1/4_Synth_Si_Grave_T.wav", 
                        "./Mode_1/4_Synth_La_Grave_T.wav", 
                        "./Mode_1/4_Synth_Fa_Grave_T.wav", 
                        "./Mode_1/4_Synth_Mi_Grave_T.wav", 
                        "./Mode_1/4_Synth_Re_Grave_T.wav"],     
        
        "Synthé CT" :  ["./Mode_1/5_Synth_Si_Aigu_CT.wav", 
                        "./Mode_1/5_Synth_La_Aigu_CT.wav", 
                        "./Mode_1/5_Synth_Fa_Aigu_CT.wav",
                        "./Mode_1/5_Synth_Mi_Aigu_CT.wav", 
                        "./Mode_1/5_Synth_Re_Aigu_CT.wav",
                        "./Mode_1/5_Synth_Si_Grave_CT.wav", 
                        "./Mode_1/5_Synth_La_Grave_CT.wav", 
                        "./Mode_1/5_Synth_Fa_Grave_CT.wav", 
                        "./Mode_1/5_Synth_Mi_Grave_CT.wav", 
                        "./Mode_1/5_Synth_Re_Grave_CT.wav"],
        
        "Big" :    ["./Mode_1/6_Big_Si_Aigu.wav", 
                    "./Mode_1/6_Big_La_Aigu.wav", 
                    "./Mode_1/6_Big_Fa_Aigu.wav", 
                    "./Mode_1/6_Big_Mi_Aigu.wav", 
                    "./Mode_1/6_Big_Re_Aigu.wav",
                    "./Mode_1/6_Big_Si_Grave.wav", 
                    "./Mode_1/6_Big_La_Grave.wav", 
                    "./Mode_1/6_Big_Fa_Grave.wav", 
                    "./Mode_1/6_Big_Mi_Grave.wav", 
                    "./Mode_1/6_Big_Re_Grave.wav"]}
        
        


preset1 = {"longueur" : 16,
           
            "volumes" : {"Percussion" : 10, "Basse T" : 16, "Basse CT" : 16, 
                         "Synthé T" : 10, "Synthé CT" : 10, "Big" : 10},
            
            "matrices" : {"Percussion" : [[1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1],
                                          [1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1],
                                          [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1],
                                          [0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0],
                                          [0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1],
                                          [0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
                                          [0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1],
                                          [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1],
                                          [0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0],
                                          [0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1]],
                          
                          "Basse T" :  [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Basse CT" : [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Synthé T" : [[1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0],
                                        [1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0],
                                        [1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
                                        [1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1],
                                        [0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0],
                                        [0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0],
                                        [0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0],
                                        [0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0]],
                          
                          "Synthé CT" :[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0],
                                        [0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0],
                                        [0,0,1,0,0,0,0,0,0,0,1,1,0,1,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Big" :      [[0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0],
                                        [0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0],
                                        [0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1],
                                        [1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                           }}







dico2 = {"Percussion" : ["./Mode_2/1_HH_CT.wav", 
                         "./Mode_2/1_HH_Double.wav", 
                         "./Mode_2/1_HH_Drill.wav", 
                         "./Mode_2/1_HH_Triple.wav", 
                         "./Mode_2/1_Kick.wav",
                         "./Mode_2/1_Snare.wav", 
                         "./Mode_2/1_Snare_Double.wav"],
         
         "Synthé" :    ["./Mode_2/2_Synth_La.wav", 
                        "./Mode_2/2_Synth_Sol.wav", 
                        "./Mode_2/2_Synth_Fa.wav", 
                        "./Mode_2/2_Synth_Mi.wav",
                        "./Mode_2/2_Synth_Re.wav",
                        "./Mode_2/2_Synth_Dod.wav",
                        "./Mode_2/2_Synth_Sib.wav"],  
        
        "Basse T" :["./Mode_2/3_Bass_T_La.wav", 
                    "./Mode_2/3_Bass_T_Sol.wav", 
                    "./Mode_2/3_Bass_T_Fa.wav", 
                    "./Mode_2/3_Bass_T_Mi.wav",
                    "./Mode_2/3_Bass_T_Re.wav",
                    "./Mode_2/3_Bass_T_Dod.wav",
                    "./Mode_2/3_Bass_T_Sib.wav"],     
        
        "Basse CT" :   ["./Mode_2/4_Bass_CT_La.wav", 
                        "./Mode_2/4_Bass_CT_Sol.wav",
                        "./Mode_2/4_Bass_CT_Fa.wav", 
                        "./Mode_2/4_Bass_CT_Mi.wav",
                        "./Mode_2/4_Bass_CT_Re.wav",
                        "./Mode_2/4_Bass_CT_Dod.wav",
                        "./Mode_2/4_Bass_CT_Sib.wav"],
        
        "Flute T" :["./Mode_2/5_Flute_T_La.wav", 
                    "./Mode_2/5_Flute_T_Sol.wav",
                    "./Mode_2/5_Flute_T_Fa.wav", 
                    "./Mode_2/5_Flute_T_Mi.wav",
                    "./Mode_2/5_Flute_T_Re.wav",
                    "./Mode_2/5_Flute_T_Dod.wav",
                    "./Mode_2/5_Flute_T_Sib.wav"],
        
        "Flute CT" :   ["./Mode_2/6_Flute_CT_La.wav", 
                        "./Mode_2/6_Flute_CT_Sol.wav",
                        "./Mode_2/6_Flute_CT_Fa.wav", 
                        "./Mode_2/6_Flute_CT_Mi.wav",
                        "./Mode_2/6_Flute_CT_Re.wav",
                        "./Mode_2/6_Flute_CT_Dod.wav",
                        "./Mode_2/6_Flute_CT_Sib.wav"]}



preset2 = {"longueur" : 16,
           
            "volumes" : {"Percussion" : 0, "Synthé" : 10, "Basse T" : 20, "Basse CT" : 20, "Flute T" : 10, "Flute CT" : 10},
            
            "matrices" : {"Percussion" : [[0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0],
                                          [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
                                          [1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0],
                                          [0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0],
                                          [1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0],
                                          [0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0],
                                          [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]],
                          
                          "Synthé" :   [[1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0],
                                        [0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0],
                                        [1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Basse T" :  [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1],
                                        [0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0],
                                        [1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Basse CT" : [[0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1],
                                        [0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Flute T" :  [[1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0],
                                        [0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]],
                          
                          "Flute CT" : [[0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0],
                                        [1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0],
                                        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]] }}







#############################################
#                                           #
#                                           #
#            Classe du Timer                #
#                                           #
#                                           #
#                                           #
#                                           #
#############################################







class MonTimer:

    def __init__(self, delai, fonction, longueur) :
        self.delai = delai
        self.fonction = fonction
        self.column = 0
        self.longueur = longueur
        self.timer = Timer(self.delai, self.run)

    def start (self) :
        self.column = -1
        self.run()

        

    def run(self) :
        self.timer = Timer(self.delai , self.run)
        self.timer.start ()
        temp = self.column
        if self.column == self.longueur-1:
            self.column = 0
        else :
            self.column += 1
        
        self.fonction (temp)
        

    def cancel(self) :
        self.timer.cancel ()





#############################################
#                                           #
#                                           #
#         Classe principale                 #
#                                           #
#                                           #
#                                           #
#                                           #
#############################################






class boite_a_musique :
    
    
    
    
    def __init__(self, audios1, audios2):
        
        
        self.dictionnaires = [audios1[0], audios2[0]]
        self.configs_temps = [audios1[1], audios2[1]]
        self.presets = [audios1[2], audios2[2]]
        self.menu()
        
        
        
        
#############################################
#                                           #
#                                           #
#         Code de la fenêtre                #
#         Menu                              #
#                                           #
#                                           #
#                                           #
#############################################
        
        
        
        
    def menu(self):
        """
        Lance la fenêtre Menu
        Entrée : None
        Sortie : None
        """
        
        #Initialisation de la fenêtre
        self.racine = ctk.CTk(fg_color = "grey20")
        self.racine.geometry("650x500")
        self.racine.resizable(False, False)
        self.racine.title("Music Box")
        self.preset_coché = False
        self.photo_headphones = ImageTk.PhotoImage((Image.open("./image/headphones_white.png")).resize((125,125), Image.LANCZOS))
        
        
        self.placeholder = ctk.CTkLabel(self.racine, text = "\n", fg_color = "grey20")
        self.placeholder.pack(side=tk.BOTTOM)
        
        
        #Création des widgets
        self.titre = ctk.CTkLabel(self.racine, text = "\nMusic Box", text_color = "white",
                                  font = ("Eras Bold ITC", 30), fg_color = "grey20")
        self.titre.pack(anchor = tk.CENTER)
        
        self.texte_longueur = ctk.CTkLabel(self.racine, font = ("Eras Bold ITC", 17), fg_color = "grey20",
                                           text = "\n\n\n\nLongueur de la grille : 4\n",
                                            text_color = "white")
        self.texte_longueur.pack(anchor = tk.CENTER)
        
        
        #Slider de taille de grille
        self.taille_choisie = tk.IntVar()
        self.scale = ctk.CTkSlider(self.racine, width=160, height=16, command = self.indicateur,
                                 border_width=5.5, variable = self.taille_choisie,
                                 from_ = 4, to = 32)
        self.scale.pack(side=tk.TOP, anchor = tk.CENTER)
        
        self.placeholder = ctk.CTkLabel(self.racine, text = "\n")
        self.placeholder.pack(side=tk.TOP, anchor = tk.CENTER)
        
        
        self.image = ctk.CTkLabel(self.racine, image = self.photo_headphones, text = "",
                                  fg_color = "grey20")
        self.image.pack(anchor = tk.CENTER)
        
        
        self.texte = ctk.CTkLabel(self.racine, text = "\nPour une meilleur écoute,\nnous recommandons l'utilisation d'écouteurs\n", 
                                  font = ("Eras Demi ITC", 17), fg_color = "grey20",
                                   text_color = "white")
        self.texte.pack(anchor = tk.CENTER)
        
        
        #Bouton de lancement de la configuration 1
        self.bouton_mode_1 = ctk.CTkButton(self.racine, text = "Configuration 1",
                    width = 10, command = self.lancer_config_1,
                    fg_color = "DodgerBlue3", hover_color = "DodgerBlue2",
                    font = ("Eras Demi ITC", 20), border_spacing = 8)
        self.bouton_mode_1.pack(anchor = tk.S, side = tk.LEFT)
        
        
        #Bouton de lancement de la configuration 2
        self.bouton_mode_2 = ctk.CTkButton(self.racine, text = "Configuration 2", 
                    width = 10, command = self.lancer_config_2,
                    fg_color = "DodgerBlue3", hover_color = "DodgerBlue2",
                    font = ("Eras Demi ITC", 20), border_spacing = 8)
        self.bouton_mode_2.pack(anchor = tk.S, side = tk.RIGHT)
        
        
        #Bouton de sélection du preset
        self.bouton_preset = ctk.CTkButton(self.racine, text = "Preset", 
                    corner_radius = 10,
                    width = 10, command = self.preset_selection,
                    fg_color = "DodgerBlue3", hover_color = "DodgerBlue2",
                    font = ("Eras Demi ITC", 20), border_spacing = 8)
        self.bouton_preset.pack(anchor = tk.CENTER, side = tk.BOTTOM)  
        

        self.racine.mainloop()
        
        
        
    def preset_selection(self):
        """
        Activation du preset pour le mode qui sera choisi
        Entrée : None
        Sortie : None
        """
        
        if self.preset_coché == False :
            
            self.preset_coché = True
            self.bouton_preset.configure(fg_color = "green2", hover_color = "green3")
            
        else : 
            
            self.preset_coché = False
            self.bouton_preset.configure(fg_color = "DodgerBlue3", hover_color = "DodgerBlue2")
            
            
            
    def indicateur(self, valeur):
        """
        Affiche la taille sélectionnée sur le slider correspondant à valeur
        Entrée : int valeur
        Sortie : None
        """ 
        
        self.texte_longueur.configure(text = f"\n\n\n\nLongueur de la grille : {self.taille_choisie.get()}\n")    
    
    
    
    def lancer_config_1(self):
        """
        Ferme le menu et lance la fenêtre correspondant à la configuration 1
        Entrée : None
        Sortie : None
        """
        
        self.racine.destroy()
        self.dico_sons = self.dictionnaires[0]
        self.temps = self.configs_temps[0]
        
        #Sélection de la taille en fonction du preset
        if self.preset_coché :
            
            self.preset = self.presets[0]
            self.longueur =self.preset["longueur"]
            
        else :
            
            if self.taille_choisie.get() != 0 :
                
                self.longueur = int(self.taille_choisie.get())
                
            else :
                
                self.longueur = 4
                
        self.fenetre_principale()
        
    
    
    
    
    def lancer_config_2(self):
        """
        Ferme le menu et lance la fenêtre correspondant à la configuration 2
        Entrée : None
        Sortie : None
        """
        
        self.racine.destroy()
        self.dico_sons = self.dictionnaires[1]
        self.temps = self.configs_temps[1]
        
        #Sélection de la taille en fonction du preset
        if self.preset_coché :
            
            self.preset = self.presets[1].copy()
            self.longueur =self.preset["longueur"]
            
        else :
            
            if self.taille_choisie.get() != 0 :
                
                self.longueur = int(self.taille_choisie.get())
                
            else :
                
                self.longueur = 4
                
        self.fenetre_principale()
        





#############################################
#                                           #
#                                           #
#          Code de la fenêtre               #
#          principale                       #
#                                           #
#                                           #
#                                           #
#############################################




    def fenetre_principale(self):
        """
        Lance la fenêtre Boîte à musique
        Entrée : None
        Sortie : None
        """
        
        #Initialisation de la fenêtre
        self.racine =  ctk.CTk(fg_color = "grey20")
        self.racine.resizable(False, False)
        self.racine.title("Music Box")
        
        
        #Récupération des images et redimentionnement
        self.photo0 = tk.PhotoImage(width = 1, height = 1)
        self.photo1a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_1.png")).resize((58,58), Image.LANCZOS))
        self.photo2a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_2.png")).resize((58,58), Image.LANCZOS))
        self.photo3a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_3.png")).resize((58,58), Image.LANCZOS))
        self.photo4a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_4.png")).resize((58,58), Image.LANCZOS))
        self.photo5a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_5.png")).resize((58,58), Image.LANCZOS))
        self.photo6a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_6.png")).resize((58,58), Image.LANCZOS))
        self.photo7a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_7.png")).resize((58,58), Image.LANCZOS))
        self.photo8a = ImageTk.PhotoImage((Image.open("./image/button_uncheck_8.png")).resize((58,58), Image.LANCZOS))
        self.photo1b = ImageTk.PhotoImage((Image.open("./image/button_check_1.png")).resize((58,58), Image.LANCZOS))
        self.photo2b = ImageTk.PhotoImage((Image.open("./image/button_check_2.png")).resize((58,58), Image.LANCZOS))
        self.photo3b = ImageTk.PhotoImage((Image.open("./image/button_check_3.png")).resize((58,58), Image.LANCZOS))
        self.photo4b = ImageTk.PhotoImage((Image.open("./image/button_check_4.png")).resize((58,58), Image.LANCZOS))
        self.photo5b = ImageTk.PhotoImage((Image.open("./image/button_check_5.png")).resize((58,58), Image.LANCZOS))
        self.photo6b = ImageTk.PhotoImage((Image.open("./image/button_check_6.png")).resize((58,58), Image.LANCZOS))
        self.photo7b = ImageTk.PhotoImage((Image.open("./image/button_check_7.png")).resize((58,58), Image.LANCZOS))
        self.photo8b = ImageTk.PhotoImage((Image.open("./image/button_check_8.png")).resize((58,58), Image.LANCZOS))
        self.photo_play = ImageTk.PhotoImage((Image.open("./image/play_button_check.png")).resize((56,56), Image.LANCZOS))
        self.photo_pause = ImageTk.PhotoImage((Image.open("./image/play_button_uncheck.png")).resize((56,56), Image.LANCZOS))
        self.photo_rec = ImageTk.PhotoImage((Image.open("./image/rec_button_check.png")).resize((90,45), Image.LANCZOS))
        self.photo_stop_rec = ImageTk.PhotoImage((Image.open("./image/rec_button_uncheck.png")).resize((90,45), Image.LANCZOS))
        self.pixel = ImageTk.PhotoImage((Image.open("./image/pixel.png")).resize((1,1), Image.LANCZOS))
        
        
        
        #Création de la liste d'attribution des couleurs
        self.liste_couleur = [(self.photo1a, self.photo1b, "deep sky blue", "DeepSkyBlue2"), 
                              (self.photo2a, self.photo2b, "gold", "gold2"),
                              (self.photo3a, self.photo3b, "green2", "green3"),
                              (self.photo4a, self.photo4b, "DeepPink2", "DeepPink3"),
                              (self.photo5a, self.photo5b, "red2", "red3"),
                              (self.photo6a, self.photo6b, "purple2", "purple3"),
                              (self.photo7a, self.photo7b, "DeepSkyBlue2", "DeepSkyBlue3"),
                              (self.photo8a, self.photo8b, "DarkOrange1", "DarkOrange2")]
        
        self.fleche1 = ImageTk.PhotoImage((Image.open("./image/arrow down.png")).resize((58,58), Image.LANCZOS))
        self.fleche2 = ImageTk.PhotoImage((Image.open("./image/arrow down red.png")).resize((58,58), Image.LANCZOS))
        
        
        #Sélection du mode initial
        self.liste_des_modes = []
        for mode in self.dico_sons.keys():
            self.liste_des_modes.append(mode)
        self.mode = self.liste_des_modes[0]
        
        #Définition de la taille de la grille
        self.hauteur = len(self.dico_sons[self.mode])
        
        
        #Initialisation du Timer
        self.mon_timer = MonTimer(self.temps, self.play_son, self.longueur)
        

        #Initialisation des variables
        self.boutons_modes = {}
        self.matrices = {}
        self.boutons_couleurs = {}
        self.volumes = {}
        self.volume = 10
        
        self.enregistre = False
        self.enregistrement = ""
        self.lecture = False
        self.couleur = self.liste_couleur[0]
        self.isolation = False
        
        
        #Création de la fenêtre et des widgets
        self.creer_boutons()
        self.effacer_tout()
        

        if self.preset_coché :
            self.activer_preset(self.preset)

        self.racine.mainloop()
        
        
    
    
    def creer_boutons(self):
        """
        Crée les boutons de la fenêtre
        Entrée : None
        Sortie : None
        """
        
        #Boutons de la grille
        self.boutons = [[0 for i in range (self.longueur)] for i in range (self.hauteur)]
        self.boutons2 = [0 for i in range (self.longueur)]
        
        for i in range (self.longueur):
            
    
            #Indicateurs de lecture
            self.boutons2[i] = tk.Button(self.racine, borderwidth=0,
                                        image = self.fleche1, width = 52, height = 52)
            self.boutons2[i].grid(row = 0,column = i)
            
            
            #Cases musicales
            for j in range (self.hauteur):
                
                self.boutons[j][i] = tk.Button(self.racine, borderwidth=0,
                                        image = self.photo1a, width = 52, height = 52,
                                        command = self.creer_fonction(i,j))
                self.boutons[j][i].grid(row = j+1, column = i)
        
                
        
        #Normalisation de l'affichage pour équilibrer les distances
        écart = len(self.dico_sons.keys()) + 5 - self.hauteur
        
        if écart > 0 : 
            
            for i in range (écart) :
                
                #Création de bouton transparent invisible
                bouton_temp = ctk.CTkButton(self.racine, width = 40, height = 40, hover_color = "grey20",
                                            image = self.pixel, fg_color = "grey20", text = "")
                bouton_temp.grid(row = self.hauteur + i + 1)
                                      
                
                
        #Boutons de fonctionnalités        
        self.bouton1 = tk.Button(self.racine, borderwidth=0,
                                 image = self.photo_play, width = 52, height = 52,
                                 command = self.debut)
        self.bouton1.grid(column = self.longueur + 1, row = 0)
        
        self.bouton2 = tk.Button(self.racine, borderwidth=0,
                                 image = self.photo_rec, width = 83, height = 41,
                                 command = self.enregistrer)
        self.bouton2.grid(column = self.longueur + 1, row = 1)
        
        self.bouton3 = ctk.CTkButton(self.racine, text = "Effacer tout", text_color="black",
                                width = 10, command = self.effacer_tout, 
                                fg_color = "LightSteelBlue3", hover_color = "LightSteelBlue4", 
                                corner_radius = 5, font=("Eras Demi ITC", 13))
        self.bouton3.grid(column = self.longueur + 1, row = 2)
        
        
        #Boutons de changement de mode
        i = 0
        
        
        
        for mode in self.dico_sons.keys() :
            
            self.boutons_modes[mode] = ctk.CTkButton(self.racine, text = mode, 
                            hover_color = "LightSteelBlue4", text_color="black",
                            width = 10, fg_color = "LightSteelBlue3", font=("Eras Demi ITC", 13),
                            command = self.changer_mode(mode), corner_radius = 5)
            
            self.boutons_modes[mode].grid(column = self.longueur + 1, row = i+3)
            
            matrice = [[0 for i in range(self.longueur)] for i in range(self.hauteur)]
            self.matrices[mode] = matrice.copy()
            
            self.boutons_couleurs[mode] = self.liste_couleur[i]
            
            i += 1
            self.couleur = self.boutons_couleurs[mode]
            self.volumes[mode] = 10
            
        
        self.boutons_modes[self.mode].configure(fg_color = self.couleur[2], 
                                                hover_color = self.couleur[3])
        
        
        #Bouton de volume
        self.scale_volume = ctk.CTkSlider(self.racine, width=90, height=16,
                                 border_width=5.5, command = self.set_volume,
                                 from_ = 0, to = 20, number_of_steps = 21)
        self.scale_volume.set(5)
        self.scale_volume.grid(column = self.longueur + 1, row = i+3)
        
        
        #Bouton de retour au menu
        self.bouton4 = ctk.CTkButton(self.racine, text = "Isoler", width = 10, 
                                     text_color="black", font=("Eras Demi ITC", 13),
                                 command = self.isoler, fg_color = "LightSteelBlue3",
                                 hover_color = "LightSteelBlue4", corner_radius = 5)
        self.bouton4.grid(column = self.longueur + 1, row = i+4)
        
        
        #Bouton de retour au menu
        self.bouton5 = ctk.CTkButton(self.racine, text = "Menu", width = 10, 
                                     text_color="black", font=("Eras Demi ITC", 13),
                                 command = self.ouvrir_menu, fg_color = "LightSteelBlue3",
                                 hover_color = "LightSteelBlue4", corner_radius = 5)
        self.bouton5.grid(column = self.longueur + 1, row = i+5)
        
        self.changer_mode(self.mode)()
        
        
        
    def play_son(self, column) : 
        """
        Joue le fichier audio correspondant à la position column
        Entrée : int column
        Sortie : None
        """
        
        #Prise en charge de la situation initiale
        if column != -1 :
            
            
            #Initialisation de l'audio et réglage de l'indicateur de position
            audio = AudioSegment.from_file("mute.wav")
            self.boutons2[column-1].configure(image = self.fleche1)
            self.boutons2[column].configure(image = self.fleche2)
            
            
            #Prise en charge de l'isolation
            if self.isolation:
                
                
                #Superposition de tous les sons activés, avec le volume correspondant
                mode = self.mode
                volume = self.volumes[mode] - 20
                for j in range(self.hauteur):
                    if self.matrices[mode][j][column] == 1:
                        audio = audio.overlay(AudioSegment.from_file(self.dico_sons[mode][j]) + volume)
                
            
            else :
                
                
                #Superposition de tous les sons activés, avec le volume correspondant
                for mode in self.dico_sons.keys():
                    volume = self.volumes[mode] - 20
                    for j in range(self.hauteur):
                        if self.matrices[mode][j][column] == 1:
                            audio = audio.overlay(AudioSegment.from_file(self.dico_sons[mode][j]) + volume)
            
                    
            #Réglage de la durée de l'audio
            audio = audio[:self.temps*1000-1].fade_out(10)
            
            
            #Prise en charge de l'enregistrement
            if self.enregistre :
                if self.enregistrement == "" :
                    self.enregistrement = audio
                else :
                    self.enregistrement += audio
                    
            
            #Lecture du son
            play(audio)

        
    
    
    
    def debut(self):
        """"
        Lance le timer correspondant à l'attribut mon_timer et change l'aspect du bouton1
        Entrée : None
        Sortie : None
        """
        
        self.mon_timer.start()
        self.lecture = True
        self.bouton1.configure(image = self.photo_pause, command = self.fin)
        
        
        
        
    def fin(self):
        """
        Stoppe le timer correspondant à l'attribut mon_timer et change l'aspect 
        du bouton1
        Entrée : None
        Sortie : None
        """
        
        self.mon_timer.cancel()
        self.lecture = False
        self.mon_timer.column = 0
        self.bouton1.configure(image = self.photo_play, command = self.debut)
        for i in range (self.longueur):
            self.boutons2[i].configure(image=self.fleche1)
        
        
        
        
    def effacer_tout(self):
        """
        l'activation de toutes les cases musicales de la grille affichée
        Entrée : None
        Sortie : None
        """
        
        for i in range(self.longueur):
            for j in range(self.hauteur):
                if self.matrices[self.mode][j][i] == 1 :
                    self.creer_fonction(i, j)()
                    
    
    
    
    def enregistrer (self) :
        """"
        Active la fonctionnalité de l'enregistrement et change l'aspect du bouton2
        Entrée : None
        Sortie : None
        """
        
        self.enregistre = True
        self.bouton2.configure(image = self.photo_stop_rec, command = self.stop_enregistrer)
        
        
        
        
    def stop_enregistrer (self) :
        """
        Désactive la fonctionnalité de l'enregistrement et change l'aspect du bouton2, et
        enregistre le fichier audio obtenu sous le nom 00 - Musique.wav si il existe
        Entrée : None
        Sortie : None
        """
        
        self.enregistre = False
        self.bouton2.configure(image = self.photo_rec, command = self.enregistrer)
        
        if self.enregistrement != "" :
            
            self.enregistrement.export("Musique.wav", format="wav")
            self.enregistrement = ""    
        
        
        
        
    def set_volume (self, valeur) :
        """
        Actualise la valeur du volume du mode actuel en fonction de la valeur du Scale
        Entrée : valeur
        Sortie : None
        """
        
        self.volumes[self.mode] = int(valeur)
        self.volume = int(valeur)
    
    
    
    
    def creer_fonction(self, i, j):
        """
        Renvoie la fonction qui correspond à la case de coordonées (i,j)
        Entrée : int i, int j,
        Sortie : fonction f
        """
        
        def f():
            
            #Cas si la case est désactivée
            if self.matrices[self.mode][j][i] == 0 :
                self.matrices[self.mode][j][i] = 1
                self.boutons[j][i].configure(image = self.couleur[1])
            
            #Cas si la case est activée    
            elif self.matrices[self.mode][j][i] == 1 :
                self.matrices[self.mode][j][i] = 0
                self.boutons[j][i].configure(image = self.couleur[0])

        return f
    
    
    
    
    def changer_mode(self, mode) :
        """
        Renvoie la fonction qui correspond au bouton du mode
        Entrée : str mode
        Sortie : fonction f
        """
        
        def f() :
            
            #Changement des paramètres
            self.couleur = self.boutons_couleurs[mode]
            self.boutons_modes[self.mode].configure(fg_color = "LightSteelBlue3", 
                                                    hover_color = "LightSteelBlue4")
            self.boutons_modes[mode].configure(fg_color = self.couleur[2], 
                                               hover_color = self.couleur[3])
            
            
            #Actualisation l'affichage de la nouvelle grille
            for i in range(self.longueur):
                for j in range(self.hauteur):
                    self.boutons[j][i].configure(image = self.couleur[self.matrices[mode][j][i]])
            
            volume = self.volumes[mode]
            self.volume = volume
            self.scale_volume.set(volume)
            self.fin_isoler()
            
            self.mode = mode
            
            
        return f
    
    
    
    
    def isoler (self):
        """
        Active le booléen isolation pour que seul le mode actuel soit lu
        Entrée : None
        Sortie : None
        """
        self.bouton4.configure(fg_color = "SteelBlue3", command = self.fin_isoler,
                               hover_color = "SteelBlue4")
        self.isolation = True
    
    
    
    def fin_isoler(self):
        """
        désactive le booléen isolation pour une lecture complète
        Entrée : None
        Sortie : None
        """
        self.bouton4.configure(fg_color = "LightSteelBlue3", command = self.isoler, 
                              hover_color = "LightSteelBlue4")
        self.isolation = False
    
    
    
    
    def activer_preset(self, preset):  
        """
        Initialise la grille avec les paramètres du preset
        Entrée : dict preset
        Sortie : None
        """

        for mode in self.dico_sons.keys() :
            
            self.volumes = self.preset["volumes"].copy()
            self.matrices = self.preset["matrices"].copy()
            
        self.changer_mode(self.liste_des_modes[0])()

    
    
    
    def ouvrir_menu(self):
        """"
        Ferme la fenêtre actuelle et réouvre le menu
        Entrée : None
        Sortie : None
        """
        
        self.stop_enregistrer()
        self.fin()
        self.racine.destroy()
        self.menu()
                
                
        

app = boite_a_musique([dico1, 0.50, preset1], [dico2, 0.4, preset2])