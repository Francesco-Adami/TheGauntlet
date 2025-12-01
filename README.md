# The Gauntlet

**Compito in classe:** Sviluppo Unreal Engine 5 & C++  
**Autore:** Adami Francesco  
**Engine:** Unreal Engine 5.6.1

## Descrizione del Progetto

Esercitazione finale individuale con **Game Loop completo** (Menu Principale → Gameplay → Win/Lose → Menu).

---

## Architettura C++ ("The Core")

Il progetto è costruito estendendo le classi base fondamentali dell'Engine, come richiesto dalle specifiche tecniche:

### Classi Principali

* **`UGauntletGameInstance` (Custom):** Gestisce il flusso persistente tra le mappe. Contiene le funzioni per avviare il gioco (`LaunchGame`), tornare al menu (`LoadMainMenu`) e chiudere l'applicazione (`QuitGame`).
* **`AAdami_TheGauntletGameMode` (Custom):** Gestisce le regole del livello e le condizioni di vittoria/sconfitta. Comunica con la UI tramite Delegati per segnalare il "Game Over" o il "Level Completed".
* **`AAdami_TheGauntletCharacter` (Custom):** Gestisce gli attributi del giocatore (bool value per la gestione delle chiavi) e le interazioni con il mondo.

### Pattern di Comunicazione

Per disaccoppiare le dipendenze tra le classi sono stati utilizzati i seguenti pattern:

1. **Interfacce (Interfaces):**
   * `IInteractable`: Implementata da leve e porte per permettere interazioni generiche tramite il metodo `Interact()`.
   * `IDamageable`: Implementata dagli ostacoli distruttibili per gestire il sistema di danno generico.
   * `ICollectible`: Implementata dalla chiave necessaria per l'apertura di una porta nel mondo
2. **Delegati (Delegates):**
   * Utilizzo di **Multicast Delegates** nel GameMode e nel TimeButton per trasmettere eventi di stato (Morte del player, Vittoria e accensione piattaforma a tempo) alla UI e agli altri attori senza riferimenti diretti (Hard References).


