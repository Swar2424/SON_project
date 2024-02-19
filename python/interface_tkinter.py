import tkinter as tk
from threading import Timer
import customtkinter as ctk
import time
import rtmidi
import json

ctk.set_appearance_mode("System")
ctk.set_default_color_theme("blue")

        
class boite_a_musique :
 
    def __init__(self, dico1, dico2):
        """
        Lance l'init
        Entrée : None
        Sortie : None
        """
        
        #Initialisation de la fenêtre
        self.out = rtmidi.MidiOut()
        self.out.open_port(1)
        
        self.racine = ctk.CTk(fg_color = "grey20")
        self.racine.geometry("550x500")
        self.racine.resizable(False, False)
        self.racine.title("Midi Teensy")
        self.instru_coché = False
        self.N = 5
        self.notes = [0 for i in range (self.N)]
        self.key_memory = {}
        self.dico_notes = dico1
        self.dico_names = dico2
        self.chords = False
        self.c_modes = {
            "MAJ" : {"5" : [0, 4, 7], "6" : [0, 4, 7, 9], "7" : [0, 4, 7, 10], "9" : [0, 3, 7, 10, 13]},
            "MIN" : {"5": [0, 3, 7], "6" : [0, 3, 7, 9], "7" : [0, 3, 7, 10], "9" : [0, 4, 7, 10, 13]}
        }
        self.c_m_current = "MAJ"
        self.c_d_current = "5"
        
        

        
        

        #Création des widgets --------------------------------------------------
        self.placeholder = ctk.CTkLabel(self.racine, text = "\n", fg_color = "grey20")
        self.placeholder.pack(side=tk.BOTTOM)
        
        
        #Titre
        self.titre = ctk.CTkLabel(self.racine, text = "\nMidi Teensy\n\n\n", text_color = "white",
                                  font = ("Eras Bold ITC", 30), fg_color = "grey20")
        self.titre.pack(anchor = tk.CENTER)
        
        
        #Affichage des notes
        self.note_label = []
        for i in range (self.N) :
            self.note_label.append(ctk.CTkLabel(self.racine, text = " __ ",
                                  font = ("Eras Bold ITC", 20), fg_color = "grey20",
                                  width=100, height=30))
            self.note_label[i].place(relx = 1/self.N*i, rely = 0.4)
        
        
        #Bouton de mode
        self.bouton_mode = ctk.CTkButton(self.racine, text = "Major",
                    width = 10, command = self.chords_m_select,
                    fg_color = "DodgerBlue3", hover_color = "DodgerBlue2",
                    font = ("Eras Demi ITC", 20), border_spacing = 8)
        self.bouton_mode.pack(anchor = tk.S, side = tk.LEFT, padx = 20)
        
        
        #Boutons chord 
        self.boutons_deg = {}
        dic_equi = {"5" : "V", "6" : "VI", "7" : "VII", "9" : "IX"}
        for i in [5,6,7,9] :
            self.boutons_deg[str(i)] = (ctk.CTkButton(self.racine, text = dic_equi[str(i)],
                        width = 10, command = self.chords_d_select(i),
                        fg_color = "DodgerBlue3", hover_color = "DodgerBlue2",
                        font = ("Eras Demi ITC", 20), border_spacing = 8))
            self.boutons_deg[str(i)].pack(anchor = tk.S, side = tk.LEFT, padx = 18)      
        
        
        #Bouton de sélection de l'instrument
        self.bouton_instru = ctk.CTkButton(self.racine, text = "Organ", 
                    corner_radius = 10,
                    width = 10, command = self.instru_selection,
                    fg_color = "DodgerBlue3", hover_color = "DodgerBlue2",
                    font = ("Eras Demi ITC", 20), border_spacing = 8)
        self.bouton_instru.pack(anchor = tk.SW, side = tk.RIGHT, padx = 20) 
          
        
        self.racine.bind("<KeyRelease>", self.fin_note)
        self.racine.bind("<Key>", self.debut_note)
        

        self.racine.mainloop()
        
        
        
    def chords_m_select(self):
        """
        Activation du preset pour le mode qui sera choisi
        Entrée : None
        Sortie : None
        """
        
        if self.c_m_current == "MAJ" :
            self.c_m_current = "MIN"
            self.bouton_mode.configure(text = "Minor")
            
        elif self.c_m_current == "MIN" :      
            self.c_m_current = "MAJ"
            self.bouton_mode.configure(text = "Major")   
   
   
            
    def chords_d_select(self, d):
        """
        Activation du preset pour le mode qui sera choisi
        Entrée : None
        Sortie : None
        """
        
        def func() :
            self.boutons_deg[self.c_d_current].configure(fg_color = "DodgerBlue3", hover_color = "DodgerBlue2")      
            self.c_d_current = str(d)
            self.boutons_deg[str(d)].configure(fg_color = "green2", hover_color = "green3")     
        
        return func
        
        
        
    def instru_selection(self):
        """
        Activation du preset pour le mode qui sera choisi
        Entrée : None
        Sortie : None
        """
        
        if self.instru_coché == False :
            self.instru_coché = True
            self.bouton_instru.configure(text = "Piano")
            note_on = [0x94, 2, 100]
            self.out.send_message(note_on)
            time.sleep(0.1)
            note_off = [0x84, 2, 0]
            self.out.send_message(note_off)
            
        else :      
            self.instru_coché = False
            self.bouton_instru.configure(text = "Organ")
            note_on = [0x94, 2, 100]
            self.out.send_message(note_on)
            time.sleep(0.1)
            note_off = [0x84, 2, 0]
            self.out.send_message(note_off)        
                
     
     
    def fin_note(self, event) :
        
        if event.keysym in self.dico_notes.keys() :
            
            list_notes = self.key_memory[event.keysym]
            self.key_memory[event.keysym] = []
            
            for x in list_notes :
                note = x + self.dico_notes[event.keysym]
                
                i = 0
                removed = False
                
                while i<(self.N) and not removed :
                    
                    if self.notes[i] == note :
                        self.notes[i] = 0
                        self.note_label[i].configure(text = " __ ")
                        removed = True
                        note_off = [0x84, note, 0]
                        self.out.send_message(note_off)
                        
                    i += 1          
        
        
        
    def debut_note(self, event) :
        
        if event.keysym in self.dico_notes.keys() and (event.keysym not in self.key_memory.keys() or self.key_memory[event.keysym] == []):

            if self.chords :
                list_notes = self.c_modes[self.c_m_current][self.c_d_current]
            else :
                list_notes = [0]
                
            self.key_memory[event.keysym] = list_notes
            
            for x in list_notes :
                note = x + self.dico_notes[event.keysym]
                
                if  note not in self.notes :
                    i = 0
                    placed = False
                    
                    while i<(self.N) and not placed :
                        
                        if self.notes[i] == 0 :
                            self.notes[i] = note
                            freq = round(pow(2, (note-69)/12)*440)
                            self.note_label[i].configure(text = f"{self.dico_names[str(note)]}\n{freq} Hz")
                            placed = True
                            note_on = [0x94, note, 100]
                            self.out.send_message(note_on)
                            
                        i += 1

                            
        elif event.keysym == "Shift_L" :
            self.chords = not self.chords
            if self.chords :
                self.bouton_mode.configure(fg_color = "green2", hover_color = "green3")
                self.boutons_deg[self.c_d_current].configure(fg_color = "green2", hover_color = "green3")
            else :
                self.bouton_mode.configure(fg_color = "DodgerBlue3", hover_color = "DodgerBlue2")
                self.boutons_deg[self.c_d_current].configure(fg_color = "DodgerBlue3", hover_color = "DodgerBlue2")
            





with open("./keynotes.json", 'r', encoding='utf-8') as file:
            donnees_lues = json.load(file)
            
app = boite_a_musique(donnees_lues["key_value"], donnees_lues["value_note"])