# Varvulado

**Descrição:**
12AX7 tube simulation VST

---

## Índice

1. [Visão Geral](#vis%C3%A3o-geral)
2. [Pré-requisitos](#pr%C3%A9-requisitos)
3. [Estrutura do Projeto](#estrutura-do-projeto)
4. [Build com JUCE e CMake](#build-com-juce-e-cmake)
5. [Configuração de Debug no Visual Studio](#configura%C3%A7%C3%A3o-de-debug-no-visual-studio)
6. [Uso do Plugin no Reaper](#uso-do-plugin-no-reaper)
7. [Scripts de Pós-build](#scripts-de-p%C3%B3s-build)
8. [Contribuição](#contribui%C3%A7%C3%A3o)
9. [Licença](#licen%C3%A7a)

---

## Visão Geral

**Varvulado** é um plugin VST3 que simula o comportamento de um pré-amplificador valvulado com tubo 12AX7, oferecendo saturação suave e caráter analógico. Utiliza modelagem por equações polinomiais e filtros RC para aproximar o som real.

---

## Pré-requisitos

* **Windows 10/11** (x64)
* **Visual Studio Community 2022**
* **JUCE 7** (incluir pasta `Juce/` no repositório ou apontar via CMake)
* **CMake** (>=3.15)
* Simulink Coder (opcional, para regenerar modelo exportado)

---

## Estrutura do Projeto

```text
Varvulado/
├── CMakeLists.txt
├── Simulink/
│   └── TubePreampModel.slx
├── Source/
│   ├── PluginProcessor.h
│   ├── PluginProcessor.cpp
│   ├── PluginEditor.h
│   ├── PluginEditor.cpp
│   ├── PluginParameters.h
│   ├── TubeModel.h
│   └── TubeModel.cpp
└── postbuild.bat  # script de pós-build (copy + manifest)
```

---

## Build com JUCE e CMake

1. **Clone o repositório**:

   ```bash
   git clone https://github.com/SeuUser/Varvulado.git
   cd Varvulado
   ```

2. **Configure CMake**:

   ```bash
   mkdir build && cd build
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```

3. **Build**:

   * Abra `Varvulado.sln` no Visual Studio 2022.
   * Selecione a configuração (Debug/Release) e pressione **Build**.

4. **Pós-build**:

   * O `postbuild.bat` copiará o `.dll` para dentro do bundle `.vst3` e gerará o manifest.

---

## Configuração de Debug no Visual Studio

1. **Debug → Debugging**:

   * **Command**: `C:\Program Files\REAPER (x64)\reaper.exe`
   * **Command Arguments** (opcional): `/start "C:\Usuários\Você\Projects\Reaper\test.rpp"`
   * **Working Directory**: `C:\Program Files\REAPER (x64)\`

2. Pressione **F5** para:

   * Compilar
   * Executar `postbuild.bat`
   * Lançar o Reaper como host do VST3 para depuração.

---

## Uso do Plugin no Reaper

1. Abra o Reaper.
2. Vá em **Options → Preferences → Plug-ins → VST** e adicione:

   ```
   C:\Program Files\Common Files\VST3
   ```
3. Clique em **Rescan**.
4. Em uma track, pressione **FX** e busque por **Varvulado**.

---

## Scripts de Pós-build

* **postbuild.bat**: copia o `.dll` para o bundle `.vst3`, limpa e gera `moduleinfo.json` via `juce_vst3_helper.exe`.
* Configurado no `CMakeLists.txt` ou no `.jucer` como:

  ```xml
  <DebugExe>... postbuild.bat</DebugExe>
  ```

---

## Contribuição

1. Faça um fork do projeto.
2. Crie uma branch (`git checkout -b feature/foo`).
3. Commit suas alterações (`git commit -m 'Add foo'`).
4. Push para a branch (`git push origin feature/foo`).
5. Abra um Pull Request.

---

## Licença

Este projeto é licenciado sob a MIT License. Veja **LICENSE** para detalhes.
