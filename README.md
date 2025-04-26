# Animation

## But

The aim of this project is to discover skeleton animation through an existing architecture and understand the involvement of mathematics in 3D animation.

### Informations

    1. The animations are sampled at **30 fps**.
    2. The lib used for the project **Whitebox** is unstable. *Sometimes the mesh   can disapear try to reload the project*.
    3. The project can only compile on **x86**. *Whitebox is not compatible **x64** *.
    4. Walk animation is not completly fluid. It is missing one frame which causes jolts.
    5. Project model and animation are from Unreal Engine 4 so the scale is 1 equal to 1 cm.

## Subject

We had to take over the existing code base and using the existing functions in Engine.h.

### Step 1

Draw the skeleton bind pose with line, using DrawLine.

### Step 2

**Draw the skeletal at the first frame of the walk animation**.
Then implement the animation at 30 keyframes per second (to move the wireframe skeleton).

### Step 3

Now that the skeleton is moving, we had to animate the mesh, which remained in T-pose.

Code the hardware skinning so that the vertices follow the bones (send the palette matrix via the SetSkinningPose function in Engine.h).

Calculate the skinning matrix on the CPU side : you cannot send inverse bind poses to the shader.

You will need to modify the vertex shader skinning.vs located in the Data/Resources folder.

The indices and weights data (boneIndices and boneWeights) are filles in for you. Just use them.

If you make a mistake in the vertex shader, the error should be displayed in the console when you launch the program.

### Step 4

Your mesh should now follow the animation's movements at 30 frames per second.

It should therefore appear jerky, because an animation frame lasts longer than a rendering frame (to convince yourself, play the animation at 0.1x speed, for example).

In technical terms, this is called constant sampling.

To improve rendering fluidity, interpolate poses between keyframes during skinning using linear sampling.

You will use an algorithm like Lerp, Slerp, Nlerp to interpolate; the choice is yours. (Slerp more "correct" but Nlerp is less expensive)

The idea would be to interpolate the QT (Quat/Translation) structure because, as you know, directly interpolating rotation matrices is mathematically "wrong" (the "intermediate" matrices are not orthonormal).

# Using

In `void MySimulation::update(float frameTime)` you can uncoment to see each step one by one.
`///*Process steps*/`
`step1(frameTime);`
`//step2(frameTime);`
`//step3(frameTime);`
`//step4(frameTime);`

You can change the speed of the animation in the same function by uncomenting and change `10.f` by another float.
`///*Limit the frame time*/`
`//if (frameTime > 0.1f)`
`//{`
`//	frameTime = 1.0f / 60.0f;`
`//}`
`//frameTime /= 10.0f;`

## Keyboard

| Input | Description |
| ----------- | ----------- |
| W | Move forward |
| A | Move Left |
| S | Move backward |
| D | Move right |
| Mouse | Look around |