# 🦷 The Sacred Dental Management System 

*"In the name of clean teeth and proper documentation"*

## Divine Features

- Appointment CRUD operations through ancient C rituals
- Data persistence via the holy `appointments.txt` scrolls
- Blessed input validation (mostly)

## 🏺 Technical Artifacts

- Written in Pure C (C99 standard)
- File I/O with `stdio.h` mysticism 
- Linked list data structure for the appointment records
- Memory management through malloc/free ceremonies

## 🕯️ Known Sacred Quirks 

1. **The Null Pointer Prophecy**
   - System may crash if memory allocation fails
   - NULL checks are more like prayers than actual validation

2. **The Buffer Overflow Curse**
   - Character arrays are fixed at 50 chars
   - Names longer than 50 chars will be truncated
   - May summon undefined behavior demons

3. **The Date Validation Ritual**
   - Accepts dates like 31/02/2024 without question
   - All dates are considered valid if they match DD/MM/YYYY
   - Time is merely a mortal construct anyway

## 📜 Usage Scrolls

1. Compile the ancient texts:
```bash
gcc dental-work.c -o dental-work
```

2. Invoke the program:
```bash
./dental-work
```

3. Follow the numeric incantations (1-5) as prompted

## 🪦 Data Storage Practices

Appointments are stored in `appointments.txt` with the following sacred format:
```
ID|DATE|NAME|PROCEDURE_TYPE|STATUS
```

## ⚠️ Warnings from the Elders

- Deleting `appointments.txt` will anger the appointment spirits
- Do not attempt to manually edit the sacred texts
- Always close the program properly or risk corrupting the appointment realm

*May your pointers be null-checked and your memory be freed. Amen.*