import time
import rtmidi
import kbhit_file


out = rtmidi.MidiOut()
ports = out.get_ports()
out.open_port(1)
dico_notes = [(119,36), (120,37), (99,38), (118,39), (98,40), (110,41), (44,42), (59,43), (58,44), (33,45)]
play = True
notes = [43, 45, 48, 50, 53, 53, 46, 43]
with out :
    while play == True :
        key = kbhit_file.kbhit_input()
        if key == 27 or key == 13 :
            play = False
        else :
            i = 0
            print(dico_notes[i][0])
            while dico_notes[i][0] != key:
                i += 1
            note = dico_notes[i][1]
            note_on = [0x94, note, 100]
            note_off = [0x84, note, 0]
            out.send_message(note_on)
            time.sleep(0.3)
            out.send_message(note_off)
            time.sleep(0.1)
            
del out