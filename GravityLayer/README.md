# Gravity Layer UE5 Plugin

Gravity Layer plugin enables you to upload to NFT wearables into your project. This plugin is a tool for authorizing users who own wearables from Gravity Layer and loading assets into a Levels. This is the entry point for interoperable clothes. Gravity Layer plugin will be initialized with the project and NFT related functions will be called through the Gravity layer subsystem.

---

## Integration

Once, you download the plugins this repositiry as a zip file and open `GravityLayerUEPlugin-Plugins` folder. 
Copy its content to your project`s plugins folder, you can continue with enabling plugins in your projects.

```
You need to restart your project if it was open during copying the plugin content.
```

## Enable Plugins

1. Open your project, and use settings button and open plugins menu.
  
2. Search for `Gravity Layer` and select the tick to enable gravity layer plugin. This will automaticly enable dependency plugins as well.
  

- **glTFRuntime**
  
- **VaRest**
  

    3. Click on `Restart` button to enable Gravity Layer plugin. After restart you are finished with integrating gravity layer plugin into your game.

### Show Plugin Content

  To view plugin content and sample map, you need to enable **Show Plugin Content ** from `Content Browser > Settings` menu.

### Access Gravity Layer Plugin

To access gravity layer plugin you need to add gravity layer plugin into your public dependencies.

1. Open your project solution and go to project's [PROJECT_NAME].Build.cs file and add "Gravity Layer" to your public dependency modules.
  
  ```
         PublicDependencyModuleNames.AddRange(new string[]
         {
             ...
             "GravityLayer"
         });`
  ```
  
  After adding Gravity layer as a dependency to your project, you can include graravity layer subsystem to your project.
  

You can read the documentation of core plugin for further information from:

[Unreal Engine 5.0 Plugin - Gravity Layer Documentation](https://gravity-studio-digital-wear.github.io/Documentation/UE5/)
