"""
================================================================
 app.py  -  Entorno grafico para el Compilador Rust (subset)
 Proyecto 1 - Compiladores I | UNITEC
================================================================

Uso:
    python app.py
    (requiere que build/compiler este compilado con 'make')

Caracteristicas:
  - Editor con numeracion de lineas, undo, atajos de teclado
  - 3 pestanas de salida: Tokens / AST / Consola
  - Coloreo semantico en cada pestana
  - Deteccion automatica del compilador en build/compiler
  - Menu completo, barra de estado, indicador de cursor
"""

import tkinter as tk
from tkinter import filedialog, scrolledtext, messagebox, font, ttk
import subprocess
import os

# ================================================================
#  PALETA DE COLORES (GitHub Dark)
# ================================================================
C = {
    "bg":        "#0d1117",
    "panel":     "#161b22",
    "border":    "#30363d",
    "toolbar":   "#21262d",
    "text":      "#e6edf3",
    "muted":     "#8b949e",
    "accent":    "#58a6ff",
    "green":     "#3fb950",
    "red":       "#f85149",
    "yellow":    "#d29922",
    "orange":    "#f0883e",
    "purple":    "#bc8cff",
    "btn_bg":    "#21262d",
    "btn_hover": "#30363d",
    "run_bg":    "#238636",
    "run_hover": "#2ea043",
}

# ================================================================
#  ESTADO GLOBAL
# ================================================================
current_file  = None
compiler_path = None


def find_compiler():
    """Busca build/compiler relativo al script o al cwd."""
    base = os.path.dirname(os.path.abspath(__file__))
    candidates = [
        os.path.join(base,       "build", "compiler"),
        os.path.join(base, "..", "build", "compiler"),
        os.path.join(os.getcwd(),"build", "compiler"),
    ]
    for p in candidates:
        p = os.path.normpath(p)
        if os.path.isfile(p) and os.access(p, os.X_OK):
            return p
    return None


# ================================================================
#  HELPERS DE UI
# ================================================================
def make_button(parent, text, cmd, bg, hover_bg, **kw):
    b = tk.Button(
        parent, text=text, command=cmd,
        bg=bg, fg=C["text"],
        activebackground=hover_bg, activeforeground=C["text"],
        relief="flat", cursor="hand2",
        padx=12, pady=5, font=("Consolas", 9), bd=0, **kw)
    b.bind("<Enter>", lambda e: b.config(bg=hover_bg))
    b.bind("<Leave>", lambda e: b.config(bg=bg))
    return b


def append_text(widget, text, tag=None):
    widget.config(state="normal")
    if tag:
        widget.insert(tk.END, text, tag)
    else:
        widget.insert(tk.END, text)
    widget.config(state="disabled")


def limpiar_salida():
    for w in (out_tokens, out_ast, out_console):
        w.config(state="normal")
        w.delete("1.0", tk.END)
        w.config(state="disabled")


# ================================================================
#  MANEJO DE ARCHIVOS
# ================================================================
def abrir_archivo():
    global current_file
    path = filedialog.askopenfilename(
        filetypes=[("Rust Files", "*.rs"), ("All Files", "*.*")])
    if not path:
        return
    current_file = path
    with open(path, "r", encoding="utf-8") as f:
        editor.delete("1.0", tk.END)
        editor.insert(tk.END, f.read())
    root.title(f"Compilador Rust  -  {os.path.basename(path)}")
    actualizar_estado(f"Archivo: {os.path.basename(path)}")
    actualizar_numeros_linea()


def guardar_archivo():
    global current_file
    if current_file:
        with open(current_file, "w", encoding="utf-8") as f:
            f.write(editor.get("1.0", tk.END))
        actualizar_estado(f"Guardado: {os.path.basename(current_file)}")
    else:
        guardar_como()


def guardar_como():
    global current_file
    path = filedialog.asksaveasfilename(
        defaultextension=".rs",
        filetypes=[("Rust Files", "*.rs")])
    if not path:
        return
    current_file = path
    with open(path, "w", encoding="utf-8") as f:
        f.write(editor.get("1.0", tk.END))
    root.title(f"Compilador Rust  -  {os.path.basename(path)}")
    actualizar_estado(f"Guardado: {os.path.basename(path)}")


def nuevo_archivo():
    global current_file
    if not messagebox.askyesno("Nuevo archivo",
                                "Descartar cambios y crear archivo nuevo?"):
        return
    current_file = None
    editor.delete("1.0", tk.END)
    limpiar_salida()
    root.title("Compilador Rust  -  UNITEC")
    actualizar_estado("Listo")
    actualizar_numeros_linea()


def seleccionar_compilador():
    global compiler_path
    path = filedialog.askopenfilename(
        title="Seleccionar ejecutable del compilador")
    if path:
        compiler_path = path
        actualizar_estado(f"Compilador: {path}")


# ================================================================
#  EJECUCION DEL COMPILADOR
# ================================================================
def ejecutar_codigo():
    global compiler_path

    # Resolver ruta del compilador
    if not compiler_path:
        compiler_path = find_compiler()

    if not compiler_path:
        limpiar_salida()
        append_text(out_console,
            "ERROR: Compilador no encontrado.\n\n"
            "  Ejecuta 'make' en la raiz del proyecto para\n"
            "  generar build/compiler, luego vuelve a intentarlo.\n\n"
            "  O usa el menu: Archivo -> Seleccionar compilador...\n",
            "error")
        notebook.select(tab_console)
        actualizar_estado("ERROR: Compilador no encontrado")
        return

    # Guardar codigo en archivo temporal junto al script
    codigo  = editor.get("1.0", tk.END)
    base    = os.path.dirname(os.path.abspath(__file__))
    tmp     = os.path.join(base, "_temp_compile.rs")

    with open(tmp, "w", encoding="utf-8") as f:
        f.write(codigo)

    limpiar_salida()
    actualizar_estado("Analizando...")
    root.update_idletasks()

    try:
        proc = subprocess.run(
            [compiler_path, tmp],
            capture_output=True, text=True, timeout=15)
        _distribuir_salida(proc.stdout, proc.stderr, proc.returncode)

    except FileNotFoundError:
        append_text(out_console,
            f"ERROR: No se pudo ejecutar:\n  {compiler_path}\n"
            "Verifica que el archivo sea ejecutable.\n", "error")
        notebook.select(tab_console)
        actualizar_estado("ERROR: No se pudo ejecutar el compilador")

    except subprocess.TimeoutExpired:
        append_text(out_console,
            "ERROR: Tiempo de analisis agotado (15s)\n", "error")
        actualizar_estado("ERROR: Tiempo agotado")

    except Exception as exc:
        append_text(out_console, f"ERROR inesperado: {exc}\n", "error")
        actualizar_estado("ERROR inesperado")

    finally:
        try:
            os.remove(tmp)
        except Exception:
            pass


# ================================================================
#  DISTRIBUCION DE SALIDA EN PESTANAS
#
#  El compilador imprime marcadores en stdout:
#    ###TOKENS###  ->  todo lo que siga va a pestana Tokens
#    ###AST###     ->  todo lo que siga va a pestana AST
#    ###FIN###     ->  todo lo que siga va a pestana Consola
#  stderr siempre va a Consola.
# ================================================================
def _distribuir_salida(stdout, stderr, returncode):
    section = "console"

    for line in stdout.splitlines():
        if   "###TOKENS###" in line:
            section = "tokens"
            continue
        elif "###AST###"    in line:
            section = "ast"
            continue
        elif "###FIN###"    in line:
            section = "console"
            continue

        if   section == "tokens":  _linea_token(line)
        elif section == "ast":     _linea_ast(line)
        else:                      _linea_consola(line)

    # stderr -> siempre Consola
    if stderr:
        append_text(out_console, "\n-- Errores --\n", "header")
        for line in stderr.splitlines():
            up = line.upper()
            if "ERROR"   in up: tag = "error"
            elif "WARNING" in up: tag = "warning"
            else:                 tag = "muted"
            append_text(out_console, line + "\n", tag)

    # Estado final
    if returncode == 0:
        append_text(out_console,
            "\n  Analisis completado exitosamente\n", "success")
        actualizar_estado("Analisis exitoso")
        notebook.select(tab_tokens)
    else:
        append_text(out_console,
            "\n  Se encontraron errores\n", "error")
        actualizar_estado("Errores encontrados")
        notebook.select(tab_console)


# ================================================================
#  COLOREO DE LINEAS POR PESTANA
# ================================================================
def _linea_token(line):
    """Colorea una linea de token segun su tipo."""
    s = line.strip()
    if not s or s.startswith("-"):
        return
    if s.startswith("[L"):
        end = line.find("]")
        if end != -1:
            pos  = line[:end + 1]
            rest = line[end + 1:]
            append_text(out_tokens, pos, "muted")
            tipo = rest.strip().split()[0] if rest.strip() else ""
            if   tipo.startswith("KW_"):                     tag = "keyword"
            elif tipo == "TYPE":                             tag = "type_tok"
            elif tipo.startswith("LIT_"):                    tag = "literal"
            elif tipo == "PRINTLN":                          tag = "keyword"
            elif tipo.startswith("OP_") or tipo == "ASSIGN": tag = "operator"
            elif tipo in ("ARROW", "DOT_DOT"):               tag = "operator"
            elif tipo == "IDENTIFIER":                       tag = "ident"
            else:                                            tag = "delim"
            append_text(out_tokens, rest + "\n", tag)
        else:
            append_text(out_tokens, line + "\n", "normal")
    else:
        append_text(out_tokens, line + "\n", "header")


def _linea_ast(line):
    """Colorea una linea del AST segun el tipo de nodo."""
    s = line.strip()
    if not s or s.startswith("-"):
        return
    if   s.startswith("Function"):                           tag = "ast_func"
    elif s.startswith("Let") or s.startswith("Assign"):     tag = "ast_let"
    elif any(s.startswith(k) for k in
             ("If","While","For","Return")):                  tag = "ast_ctrl"
    elif s.startswith("BinaryOp") or s.startswith("UnaryOp"): tag = "ast_op"
    elif s.startswith("Call"):                               tag = "ast_call"
    elif s.startswith("Literal"):                            tag = "ast_lit"
    elif s.startswith("Identifier"):                         tag = "ast_id"
    elif s.startswith("Program") or s.startswith("Block") \
         or s.startswith("Param"):                           tag = "header"
    else:                                                    tag = "normal"
    append_text(out_ast, line + "\n", tag)


def _linea_consola(line):
    """Colorea una linea de la seccion Consola."""
    s = line.strip()
    if not s:
        append_text(out_console, "\n")
        return
    if   "exitosamente" in s:         tag = "success"
    elif "RESULTADO" in s \
         and "error" in s.lower():    tag = "error"
    elif s.startswith("===") \
         or s.startswith("---"):      tag = "header"
    else:                             tag = "normal"
    append_text(out_console, line + "\n", tag)


# ================================================================
#  BARRA DE ESTADO Y NUMEROS DE LINEA
# ================================================================
def actualizar_estado(msg="Listo"):
    status_label.config(text=f"  {msg}")


def actualizar_numeros_linea(event=None):
    lineas = editor.get("1.0", tk.END).count("\n")
    nums   = "\n".join(str(i) for i in range(1, lineas + 2))
    line_numbers.config(state="normal")
    line_numbers.delete("1.0", tk.END)
    line_numbers.insert("1.0", nums)
    line_numbers.config(state="disabled")


def actualizar_cursor(event=None):
    try:
        pos      = editor.index(tk.INSERT)
        ln, col  = pos.split(".")
        cursor_label.config(text=f"Ln {ln}, Col {int(col)+1}  ")
    except Exception:
        pass


def bind_shortcuts():
    root.bind("<Control-o>",      lambda e: abrir_archivo())
    root.bind("<Control-s>",      lambda e: guardar_archivo())
    root.bind("<Control-Return>", lambda e: ejecutar_codigo())
    root.bind("<Control-n>",      lambda e: nuevo_archivo())
    editor.bind("<KeyRelease>",
        lambda e: (actualizar_numeros_linea(), actualizar_cursor(e)))
    editor.bind("<ButtonRelease>", actualizar_cursor)


# ================================================================
#  CONSTRUCCION DE LA VENTANA
# ================================================================
root = tk.Tk()
root.title("Compilador Rust  -  UNITEC")
root.geometry("1100x800")
root.minsize(750, 550)
root.configure(bg=C["bg"])

# ---- Menu ----
menubar = tk.Menu(root, bg=C["toolbar"], fg=C["text"],
                  activebackground=C["accent"], activeforeground="white",
                  relief="flat", bd=0)

m_arch = tk.Menu(menubar, tearoff=0, bg=C["toolbar"], fg=C["text"],
                 activebackground=C["accent"], activeforeground="white")
m_arch.add_command(label="Nuevo              Ctrl+N", command=nuevo_archivo)
m_arch.add_command(label="Abrir...           Ctrl+O", command=abrir_archivo)
m_arch.add_separator()
m_arch.add_command(label="Guardar            Ctrl+S", command=guardar_archivo)
m_arch.add_command(label="Guardar como...",           command=guardar_como)
m_arch.add_separator()
m_arch.add_command(label="Seleccionar compilador...", command=seleccionar_compilador)
m_arch.add_separator()
m_arch.add_command(label="Salir",                     command=root.quit)
menubar.add_cascade(label="Archivo", menu=m_arch)

m_run = tk.Menu(menubar, tearoff=0, bg=C["toolbar"], fg=C["text"],
                activebackground=C["accent"], activeforeground="white")
m_run.add_command(label="Analizar   Ctrl+Enter", command=ejecutar_codigo)
m_run.add_command(label="Limpiar salida",         command=limpiar_salida)
menubar.add_cascade(label="Ejecutar", menu=m_run)

root.config(menu=menubar)

# ---- Toolbar ----
toolbar = tk.Frame(root, bg=C["toolbar"], pady=6)
toolbar.pack(fill="x")

make_button(toolbar, "Nuevo",   nuevo_archivo,   C["btn_bg"], C["btn_hover"]).pack(side="left", padx=(8,2))
make_button(toolbar, "Abrir",   abrir_archivo,   C["btn_bg"], C["btn_hover"]).pack(side="left", padx=2)
make_button(toolbar, "Guardar", guardar_archivo, C["btn_bg"], C["btn_hover"]).pack(side="left", padx=2)
tk.Frame(toolbar, bg=C["border"], width=1, height=24).pack(side="left", padx=10, pady=2)
make_button(toolbar, "Analizar  Ctrl+Enter", ejecutar_codigo,
            C["run_bg"], C["run_hover"]).pack(side="left", padx=2)
make_button(toolbar, "Limpiar", limpiar_salida, C["btn_bg"], C["btn_hover"]).pack(side="left", padx=2)

# ---- Panel divisor vertical ----
pane = tk.PanedWindow(root, orient=tk.VERTICAL, bg=C["border"],
                       sashwidth=5, sashpad=0, sashrelief="flat")
pane.pack(fill="both", expand=True)

# ---- Panel Editor ----
ef = tk.Frame(pane, bg=C["bg"])
tk.Label(ef, text="  EDITOR", bg=C["panel"], fg=C["muted"],
         font=("Consolas", 8, "bold"), anchor="w", pady=4).pack(fill="x")

ei = tk.Frame(ef, bg=C["panel"])
ei.pack(fill="both", expand=True)

mono = font.Font(family="Consolas", size=11)

line_numbers = tk.Text(ei, width=4, bg=C["panel"], fg=C["muted"],
                        state="disabled", font=mono, bd=0, pady=5,
                        selectbackground=C["panel"], cursor="arrow")
line_numbers.pack(side="left", fill="y")

tk.Frame(ei, bg=C["border"], width=1).pack(side="left", fill="y")

editor = scrolledtext.ScrolledText(
    ei, bg=C["panel"], fg=C["text"],
    insertbackground=C["accent"], font=mono,
    relief="flat", bd=0, pady=5, padx=8,
    selectbackground="#264f78", wrap="none", undo=True)
editor.pack(fill="both", expand=True)
pane.add(ef, minsize=150)

# ---- Panel de salida con pestanas ----
of = tk.Frame(pane, bg=C["bg"])

style = ttk.Style()
style.theme_use("default")
style.configure("Dark.TNotebook",
    background=C["panel"], borderwidth=0, tabmargins=0)
style.configure("Dark.TNotebook.Tab",
    background=C["toolbar"], foreground=C["muted"],
    padding=[14, 5], font=("Consolas", 9, "bold"), borderwidth=0)
style.map("Dark.TNotebook.Tab",
    background=[("selected", C["bg"])],
    foreground=[("selected", C["text"])])

notebook  = ttk.Notebook(of, style="Dark.TNotebook")
notebook.pack(fill="both", expand=True)
out_font  = font.Font(family="Consolas", size=10)


def make_tab(label):
    fr = tk.Frame(notebook, bg=C["panel"])
    notebook.add(fr, text=f"  {label}  ")
    w  = scrolledtext.ScrolledText(
        fr, bg=C["panel"], fg=C["text"],
        font=out_font, relief="flat", bd=0,
        pady=5, padx=8, state="disabled")
    w.pack(fill="both", expand=True)
    return fr, w


tab_tokens,  out_tokens  = make_tab("Tokens")
tab_ast,     out_ast     = make_tab("AST")
tab_console, out_console = make_tab("Consola")
pane.add(of, minsize=100)

# ---- Tags: pestana Tokens ----
out_tokens.tag_config("header",  foreground=C["muted"],  font=("Consolas", 9, "bold"))
out_tokens.tag_config("keyword", foreground=C["purple"])
out_tokens.tag_config("type_tok",foreground=C["accent"])
out_tokens.tag_config("literal", foreground=C["orange"])
out_tokens.tag_config("operator",foreground=C["yellow"])
out_tokens.tag_config("ident",   foreground=C["text"])
out_tokens.tag_config("delim",   foreground=C["muted"])
out_tokens.tag_config("muted",   foreground=C["muted"])
out_tokens.tag_config("normal",  foreground=C["text"])

# ---- Tags: pestana AST ----
out_ast.tag_config("header",   foreground=C["muted"],  font=("Consolas", 10, "bold"))
out_ast.tag_config("ast_func", foreground=C["accent"], font=("Consolas", 10, "bold"))
out_ast.tag_config("ast_let",  foreground=C["purple"])
out_ast.tag_config("ast_ctrl", foreground=C["yellow"])
out_ast.tag_config("ast_op",   foreground=C["orange"])
out_ast.tag_config("ast_call", foreground=C["green"])
out_ast.tag_config("ast_lit",  foreground=C["orange"])
out_ast.tag_config("ast_id",   foreground=C["text"])
out_ast.tag_config("normal",   foreground=C["text"])

# ---- Tags: pestana Consola ----
out_console.tag_config("success", foreground=C["green"],  font=("Consolas", 10, "bold"))
out_console.tag_config("error",   foreground=C["red"])
out_console.tag_config("warning", foreground=C["yellow"])
out_console.tag_config("header",  foreground=C["muted"],  font=("Consolas", 9, "bold"))
out_console.tag_config("muted",   foreground=C["muted"])
out_console.tag_config("normal",  foreground=C["text"])

# ---- Barra de estado ----
sb = tk.Frame(root, bg=C["toolbar"], height=24)
sb.pack(fill="x", side="bottom")

status_label = tk.Label(sb, text="  Listo",
    bg=C["toolbar"], fg=C["muted"],
    font=("Consolas", 9), anchor="w")
status_label.pack(side="left", fill="x", expand=True)

tk.Label(sb, text="Ctrl+O Abrir  |  Ctrl+S Guardar  |  Ctrl+Enter Analizar  ",
    bg=C["toolbar"], fg=C["border"],
    font=("Consolas", 8)).pack(side="right")

cursor_label = tk.Label(sb, text="Ln 1, Col 1  ",
    bg=C["toolbar"], fg=C["muted"],
    font=("Consolas", 9))
cursor_label.pack(side="right")

# ---- Codigo de ejemplo (mismo que el documento del proyecto) ----
EJEMPLO = """\
// Ejemplo del documento - Compiladores I UNITEC
fn suma(a: i32, b: i32) -> i32 {
    return a + b;
}

fn main() {
    let x = 10;
    let y = 20;

    if x < y {
        let resultado = suma(x, y);
    } else {
        return;
    }
}
"""
editor.insert("1.0", EJEMPLO)

# ---- Detectar compilador al arrancar ----
compiler_path = find_compiler()
if compiler_path:
    actualizar_estado(f"Compilador listo: {compiler_path}")
else:
    actualizar_estado("Ejecuta 'make' para construir el compilador")

bind_shortcuts()
actualizar_numeros_linea()
root.mainloop()
