# DotDotio

Ett SFML-baserat spel utvecklat i C++ där du kontrollerar en spelare och samlar bollar med olika effekter. Vissa ger poäng, andra skadar dig – och vissa helar.

## Gameplay

- Du styr en grön ruta (spelaren) med WASD.
- Bollar (SwagBalls) faller ner eller placeras ut.
  - **Vanlig boll (random färg):** +1 poäng
  - **Röd (DAMAGING):** -34 HP
  - **Grön (HEALING):** +8 HP
- Spelet är slut när din HP når 0.
- Din poäng och hälsa visas i hörnet.

## Teknik

- **Språk:** C++
- **Ramverk:** SFML (Graphics, System, Window)
- **Kodstruktur:**
  - OOP med klasser: `Game`, `Player`, `SwagBall`
  - Timerbaserad spawning
  - Kollision med fönstergränser
  - Grundläggande GUI med SFML Text
