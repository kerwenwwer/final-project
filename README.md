# final-project
This is my final-project in programming language class

I using Allegro API to build my C language Project

### Install Allegro 

```bash
sudo pacman -S allegro
```

### Complier path
```bash
g++ -o $name.out $file_name.cpp $(pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5)
```