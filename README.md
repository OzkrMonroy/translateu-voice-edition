# TranslateU Voice Edition

TranslateU Voice Edition is a C++-based multilingual dictionary application that uses an AVL tree structure to manage and store words with their translations in multiple languages.  
This version integrates the **Azure Speech SDK** to enable text-to-speech functionality across supported languages like Spanish, English, French, Italian, and German.

---

## 🚀 Features

- ⚙️ **AVL Tree**: Efficient insertion, removal, and lookup of translations
- 🌍 **Multilingual Support**: Handles translations across multiple languages
- 🔊 **Text-to-Speech**: Uses Azure Speech SDK to vocalize translated words
- 💾 **File Persistence**: Save and load translation entries from disk

---

## 🛠 Tech Stack

- **C++** with Visual Studio 2022
- **Azure Speech SDK** via NuGet
- **Standard Windows Console I/O**
- Optional use of **JSON-based** file handling for persistence

---

## 📂 Folder Structure
```
.
src/
	├── models/ # AVL Tree and word data structures
	├── controllers/ # Logic handling (menu, translation manager, etc.)
	├── ui/ # User interface (console-based)
	├── utils/ # File handling, helpers, etc.

```

---

## 🔧 Prerequisites

- Windows 10/11
- Visual Studio 2022
- Azure Speech Subscription Key & Region (e.g. `eastus`, `westeurope`)
- NuGet package: `Microsoft.CognitiveServices.Speech`

---

## 🚀 Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/translateu-voice-edition.git
	 ```
2. Open the .sln file in Visual Studio

3. Install the required NuGet packages

4. Set your Azure Speech key and region in AzureAudioPlayer.cpp

5. Build and run

## 📋 License
This project is licensed under the MIT License.