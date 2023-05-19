## Motivation
For over a decade, Mojang's Java-based Minecraft Server implementation (and its
derivatives like [https://spigotmc.org](Spigot) and [https://papermc.io](Paper)
have been widely utilized in Minecraft servers of small and large scale.

Regardless of how widely this implementation is used, there are quite a few
foundational issues in its design. These issues affect the performance of the
server and cause high resource utilization. Not only that, but the developer
APIs often cause issues related to backwards compatibility and the development
environment.

There have been numerous attempts to fix these issues by projects like Paper,
which were quite successful, but we still feel like the main issue has not been
targeted yet: the runtime. Since the Mojang implementation is written in Java,
it runs on the JVM. The JVM, however, has proved over the years that it's very
inefficient, with its high memory footprint, slow startup times and bad
developer experience.

## Introducing Jam
Jam is a project that aims to solve most, if not of all of these issues. It
aims to provide a new modern and well-designed ecosystem for building High
Performance, Sustainable and Maintainable Minecraft Servers.

Jam is a groundbreaking project aiming to address the limitations and
performance issues of the current Minecraft: Java Edition server
implementation. Leveraging the power of modern programming languages and
innovative approaches, Jam seeks to deliver a highly optimized, scalable, and
robust Minecraft server experience.

## Key Objectives
Jam sets out to achieve the following objectives:

    High Performance: Utilizing C++, Jam aims to significantly improve the
    server's performance and lower the memory footprint compared to the
    existing Java implementation. This optimization will ensure smoother
    multiplayer experiences, even on weak machines.

    Scalability and Flexibility: Jam focuses on designing a modular and
    extensible server architecture that can easily adapt to varying player
    counts and server configurations. This flexibility will allow server owners
    to efficiently manage and scale their Minecraft servers.
