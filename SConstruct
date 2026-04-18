# SConstruct

# Standard Flipper Zero FAP build configuration

# Import the necessary modules
Import("env")

# Create an environment for building
env = Environment()

# Set the target application name
app_name = "my_application"

# Specify the source files
sources = [
    "main.c",
    "utils.c",
    "flipper.c",
]

# Set the build target
env.Program(target=app_name, source=sources)

# Define any required flags or libraries
env.Append(CPPDEFINES=["FLIPPER_ZERO"])
env.Append(LIBS=["mylib"])

# Specify any additional build options
env options = {}  # Add additional options here

# Execute the build
env.AlwaysBuild(env.Alias("build", env.Target(app_name)))

# Clean target
Clean(env, app_name)