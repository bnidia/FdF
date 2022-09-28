# FdF (Complexity 60 hours)
<img align="right" src="https://badge42.vercel.app/api/v2/cl3enoo9k004009muhk5a94tj/project/2464372" alt="bnidia's 42 FdF Score" />

### Wireframe model. This project is about representing a landscape as a 3D object in which all surfaces are outlined in lines.

This is the first project in which we use an external graphics library so that we can open maps of a special format and display them on the screen. Here it was necessary to deal with the formulas that are responsible for the rotation of the plane figures
![FdF Mars landscape demontration](https://github.com/bnidia/FdF/blob/master/FdF_video_demonstration.gif)

### Этот проект посвящен представлению ландшафта в виде 3D-объекта, в котором все поверхности очерчены линиями.
Это первый проект в котором мы используем внешнюю графическую библиотеку для того чтобы мы могли открывать карты специального формата и выводить их на экран. Здесь необходимо было разобраться с формулами, которые отвечают за вращение фигур плоскости

### How to build and run
Download to your computer, go to the directory FdF, compile with make and then run.
Differrent maps can be found in maps directory. 
```
git clone https://github.com/bnidia/FdF.git
cd FdF
make
./fdf ./maps/mars.fdf
```
if you have error
configure [error] : Can't find a suitable X11 include directory.

please install

sudo apt install libxext-dev
