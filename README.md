# Kotiki Engine

**Kotiki Engine** is an educational project for the "Computer Graphics" course. It simulates and illustrates the behavior of cats on a 2D plane.

![Day-scene and panel example](assets/doc/day_example.png)
![Night-scene and panel example](assets/doc/night_example.png)

## Installation (Ubuntu)

Follow these steps to install and run Kotiki Engine:
1. **Clone the repository:**
   ```bash
   git clone https://github.com/ALanovaya/kotiki-engine.git
   cd kotiki-engine
   ```
2. **Install dependencies:**
   - **Install boost**
   ```bash
   sudo apt update
   sudo apt install libboost-all-dev
   ```
   - **Install Qt and OpenGL**
   ```bash
   sudo apt-get update
   sudo apt-get install -y qt6-base-dev qt6-tools-dev libglu1-mesa-dev freeglut3-dev
   ```
3. **Build the project**
    ```bash
   cmake -B build -S .
   cmake --build build
   ```
4. **Run the application**
   ```bash
   cd build/kotiki-engine
   ./kotiki-engine
   ```

## Features

- There can be up to 50,000 cats on the map at the same time. User can set their number.
- Cats can try to start a fight, hiss and walk quietly, depending on the distance between them and the maximum distance at which they can start a fight (set by the user).
- Distance can be measured using various metrics - Euclidean, Manhattan, Chebyshev and their generalizations - the Minkowski metric.
- User can choose how the cats will move - either randomly or along a trajectory that can be specified by a parametric equation. The user must specify a parameter (let's say t) and describe the equations x(t), y(t). Otherwise, the trajectory will not be recognized.
- To determine the state of the cats, a grid lookup algorithm is used.
- It is possible to flexibly control the space and movement of the cats - change the size of the scene on which cats walk, change the step at which cats can move, and others.
- Cat activity and state (coordinates and actions) can be logged to the console, with logging toggled via a button.
- A day-night cycle affects cat behavior: at night, most cats sleep or become less active, while some may sleepwalk.

## Authors

- Alexandra Lanovaya (Telegram: @winxpopp)
- Ilya Syresenkov (Telegram: @maybenotilya)
- Rafik Nurmukhametov (Telegram: @nrrafik)
- Alexander Lekomtcev (Telegram: @al_lekomtsev)