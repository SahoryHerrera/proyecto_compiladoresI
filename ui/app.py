"""
================================================================
 app.py  -  Compilador Rust (subset) | Compiladores I UNITEC
================================================================
"""

import tkinter as tk
from tkinter import filedialog, scrolledtext, messagebox, font, ttk
import subprocess
import os
import re

# ================================================================
#  PALETA  —  One Dark Pro refinada
# ================================================================
C = {
    "bg":          "#1a1d23",
    "bg2":         "#21252b",
    "bg3":         "#282c34",
    "border":      "#3d4148",
    "border2":     "#4b5263",
    "text":        "#abb2bf",
    "text_bright": "#dde1e8",
    "muted":       "#5c6370",
    "accent":      "#61afef",
    "accent2":     "#528bff",
    "green":       "#98c379",
    "red":         "#e06c75",
    "yellow":      "#e5c07b",
    "orange":      "#d19a66",
    "purple":      "#c678dd",
    "cyan":        "#56b6c2",
    "btn":         "#2c313a",
    "btn_hover":   "#3a3f4b",
    "run":         "#3a7c3a",
    "run_hover":   "#4a9e4a",
}

# ================================================================
#  ESTADO
# ================================================================
current_file  = None
compiler_path = None
_modified     = False


def find_compiler():
    base = os.path.dirname(os.path.abspath(__file__))
    for p in [
        os.path.join(base,        "build", "compiler"),
        os.path.join(base, "..",  "build", "compiler"),
        os.path.join(os.getcwd(), "build", "compiler"),
    ]:
        p = os.path.normpath(p)
        if os.path.isfile(p) and os.access(p, os.X_OK):
            return p
    return None


# ================================================================
#  UTILIDADES UI
# ================================================================
def _btn(parent, text, cmd, bg=None, hover=None, fg=None, **kw):
    bg    = bg    or C["btn"]
    hover = hover or C["btn_hover"]
    fg    = fg    or C["text_bright"]
    b = tk.Button(parent, text=text, command=cmd,
                  bg=bg, fg=fg, activebackground=hover,
                  activeforeground=C["text_bright"],
                  relief="flat", cursor="hand2",
                  padx=14, pady=6,
                  font=("Consolas", 9), bd=0, **kw)
    b.bind("<Enter>", lambda e: b.config(bg=hover))
    b.bind("<Leave>", lambda e: b.config(bg=bg))
    return b


def _write(widget, text, tag=None):
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
    _set_tab_badge(tab_tokens,  "Tokens",  None)
    _set_tab_badge(tab_ast,     "AST",     None)
    _set_tab_badge(tab_console, "Consola", None)


# ================================================================
#  BADGES en pestanas
# ================================================================
def _set_tab_badge(tab, label, status):
    icons = {"ok": " ✓", "err": " ✗", "warn": " ⚠", None: ""}
    notebook.tab(tab, text=f"  {label}{icons[status]}  ")


# ================================================================
#  ARCHIVOS
# ================================================================
def _mark_modified():
    global _modified
    _modified = True
    title = root.title()
    if not title.startswith("● "):
        root.title("● " + title)


def _mark_saved():
    global _modified
    _modified = False
    title = root.title().lstrip("● ")
    root.title(title)


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
    root.title(f"Compilador Rust  —  {os.path.basename(path)}")
    _mark_saved()
    actualizar_estado(f"  {os.path.basename(path)}")
    actualizar_numeros_linea()
    _highlight_syntax()


def guardar_archivo(event=None):
    global current_file
    if current_file:
        with open(current_file, "w", encoding="utf-8") as f:
            f.write(editor.get("1.0", tk.END))
        _mark_saved()
        actualizar_estado(f"  Guardado — {os.path.basename(current_file)}")
    else:
        guardar_como()


def guardar_como():
    global current_file
    path = filedialog.asksaveasfilename(
        defaultextension=".rs", filetypes=[("Rust Files", "*.rs")])
    if not path:
        return
    current_file = path
    with open(path, "w", encoding="utf-8") as f:
        f.write(editor.get("1.0", tk.END))
    root.title(f"Compilador Rust  —  {os.path.basename(path)}")
    _mark_saved()
    actualizar_estado(f"  Guardado — {os.path.basename(path)}")


def nuevo_archivo():
    global current_file
    if _modified:
        if not messagebox.askyesno("Nuevo archivo",
                                   "Hay cambios sin guardar. ¿Continuar?"):
            return
    current_file = None
    editor.delete("1.0", tk.END)
    limpiar_salida()
    root.title("Compilador Rust  —  UNITEC")
    _mark_saved()
    actualizar_estado("  Listo")
    actualizar_numeros_linea()


def seleccionar_compilador():
    global compiler_path
    path = filedialog.askopenfilename(title="Seleccionar ejecutable")
    if path:
        compiler_path = path
        actualizar_estado(f"  Compilador: {os.path.basename(path)}")


# ================================================================
#  SYNTAX HIGHLIGHTING  (simple, basado en regex)
# ================================================================
KW_PATTERN = r'\b(fn|let|mut|if|else|while|for|in|return|true|false|println)\b'
TYPE_PATTERN = r'\b(i32|i64|f64|f32|bool|char|str|usize)\b'
NUM_PATTERN = r'\b\d+(\.\d+)?\b'
STR_PATTERN = r'"[^"]*"'
CHAR_PATTERN = r"'[^']*'"
CMT_PATTERN = r'//.*$'


def _highlight_syntax(event=None):
    for tag in ("hl_kw","hl_type","hl_num","hl_str","hl_cmt","hl_op"):
        editor.tag_remove(tag, "1.0", tk.END)

    content = editor.get("1.0", tk.END)
    lines   = content.split("\n")

    for lineno, line in enumerate(lines, start=1):
        def apply(pat, tag, flags=0):
            for m in re.finditer(pat, line, flags):
                s = f"{lineno}.{m.start()}"
                e = f"{lineno}.{m.end()}"
                editor.tag_add(tag, s, e)

        apply(CMT_PATTERN,  "hl_cmt")
        apply(STR_PATTERN,  "hl_str")
        apply(CHAR_PATTERN, "hl_str")
        apply(KW_PATTERN,   "hl_kw")
        apply(TYPE_PATTERN, "hl_type")
        apply(NUM_PATTERN,  "hl_num")

    root.after(0, _update_line_count)


# ================================================================
#  EJECUCION
# ================================================================
def ejecutar_codigo(event=None):
    global compiler_path

    if not compiler_path:
        compiler_path = find_compiler()

    if not compiler_path:
        limpiar_salida()
        _write(out_console,
            "  ERROR: Compilador no encontrado.\n\n"
            "  Ejecuta 'make' en la raiz del proyecto\n"
            "  para generar build/compiler.\n\n"
            "  O usa: Archivo → Seleccionar compilador...\n", "error")
        notebook.select(tab_console)
        actualizar_estado("  ERROR: Compilador no encontrado")
        return

    codigo = editor.get("1.0", tk.END)
    base   = os.path.dirname(os.path.abspath(__file__))
    tmp    = os.path.join(base, "_tmp.rs")

    with open(tmp, "w", encoding="utf-8") as f:
        f.write(codigo)

    limpiar_salida()
    actualizar_estado("  Analizando...")
    run_btn.config(text="  ⏳ Analizando...", state="disabled")
    root.update_idletasks()

    try:
        proc = subprocess.run(
            [compiler_path, tmp],
            capture_output=True, text=True, timeout=15)
        _distribuir(proc.stdout, proc.stderr, proc.returncode)
    except FileNotFoundError:
        _write(out_console, f"  ERROR: No se pudo ejecutar:\n  {compiler_path}\n", "error")
        notebook.select(tab_console)
        actualizar_estado("  ERROR al ejecutar")
    except subprocess.TimeoutExpired:
        _write(out_console, "  ERROR: Tiempo agotado (15s)\n", "error")
        actualizar_estado("  Tiempo agotado")
    except Exception as exc:
        _write(out_console, f"  ERROR: {exc}\n", "error")
    finally:
        run_btn.config(text="  ▶  Analizar", state="normal")
        try:
            os.remove(tmp)
        except Exception:
            pass


def _distribuir(stdout, stderr, returncode):
    section = "console"
    tok_count = 0

    for line in stdout.splitlines():
        if   "###TOKENS###" in line: section = "tokens"; continue
        elif "###AST###"    in line: section = "ast";    continue
        elif "###FIN###"    in line: section = "console";continue

        if   section == "tokens":
            _linea_token(line)
            if line.strip().startswith("[L"):
                tok_count += 1
        elif section == "ast":   _linea_ast(line)
        else:                    _linea_consola(line)

    if stderr:
        _write(out_console, "\n  Errores\n", "section_hdr")
        _write(out_console, "  " + "─"*40 + "\n", "dim")
        for line in stderr.splitlines():
            up = line.upper()
            tag = "error" if "ERROR" in up else "warning" if "WARNING" in up else "dim"
            _write(out_console, "  " + line + "\n", tag)

    if returncode == 0:
        _write(out_console, "\n  ✓  Analisis completado exitosamente\n", "success")
        actualizar_estado(f"  ✓  {tok_count} tokens — exitoso")
        _set_tab_badge(tab_tokens,  "Tokens",  "ok")
        _set_tab_badge(tab_ast,     "AST",     "ok")
        _set_tab_badge(tab_console, "Consola", "ok")
        notebook.select(tab_tokens)
    else:
        _write(out_console, "\n  ✗  Se encontraron errores\n", "error")
        actualizar_estado("  ✗  Errores encontrados")
        _set_tab_badge(tab_console, "Consola", "err")
        notebook.select(tab_console)


# ================================================================
#  COLOREO POR PESTANA
# ================================================================
def _linea_token(line):
    s = line.strip()
    if not s or s.startswith("-"): return
    if s.startswith("[L"):
        end = line.find("]")
        if end == -1:
            _write(out_tokens, line + "\n"); return
        pos  = line[:end+1]
        rest = line[end+1:]
        tipo = rest.strip().split()[0] if rest.strip() else ""
        _write(out_tokens, "  " + pos, "tok_pos")
        if   tipo.startswith("KW_"):                          tag = "tok_kw"
        elif tipo == "TYPE":                                  tag = "tok_type"
        elif tipo.startswith("LIT_"):                         tag = "tok_lit"
        elif tipo == "PRINTLN":                               tag = "tok_kw"
        elif tipo.startswith("OP_") or tipo in ("ASSIGN",
             "ARROW","DOT_DOT"):                              tag = "tok_op"
        elif tipo == "IDENTIFIER":                            tag = "tok_id"
        else:                                                 tag = "tok_delim"
        _write(out_tokens, rest + "\n", tag)
    else:
        _write(out_tokens, "  " + line + "\n", "dim")


def _linea_ast(line):
    s = line.strip()
    if not s or s.startswith("-"): return
    indent = len(line) - len(line.lstrip())
    pad    = "  " + " " * indent
    if   s.startswith("Function"):   tag = "ast_fn"
    elif s.startswith("Let") or s.startswith("Assign"): tag = "ast_let"
    elif any(s.startswith(k) for k in ("If","While","For","Return")): tag = "ast_ctrl"
    elif s.startswith("BinaryOp") or s.startswith("UnaryOp"): tag = "ast_op"
    elif s.startswith("Call"):        tag = "ast_call"
    elif s.startswith("Literal"):     tag = "ast_lit"
    elif s.startswith("Identifier"):  tag = "ast_id"
    elif s.startswith("Program") or s.startswith("Block") or s.startswith("Param"): tag = "ast_struct"
    else:                             tag = "ast_dim"
    _write(out_ast, pad + s + "\n", tag)


def _linea_consola(line):
    s = line.strip()
    if not s:
        _write(out_console, "\n"); return
    if   "exitosamente" in s:                               tag = "success"
    elif "RESULTADO" in s and "error" in s.lower():         tag = "error"
    elif s.startswith("===") or s.startswith("---"):        tag = "dim"
    elif s.startswith("Compilador") or s.startswith("Arch"): tag = "info"
    else:                                                   tag = "normal"
    _write(out_console, "  " + line + "\n", tag)


# ================================================================
#  ESTADO, LINEAS, CURSOR
# ================================================================
def actualizar_estado(msg="  Listo"):
    status_label.config(text=msg)


def _update_line_count(event=None):
    lineas = editor.get("1.0", tk.END).count("\n")
    nums   = "\n".join(str(i) for i in range(1, lineas + 2))
    line_numbers.config(state="normal")
    line_numbers.delete("1.0", tk.END)
    line_numbers.insert("1.0", nums)
    line_numbers.config(state="disabled")


def actualizar_numeros_linea(event=None):
    _update_line_count()


def actualizar_cursor(event=None):
    try:
        pos     = editor.index(tk.INSERT)
        ln, col = pos.split(".")
        lines   = int(editor.index("end-1c").split(".")[0])
        cursor_label.config(text=f"  Ln {ln}/{lines}  Col {int(col)+1}  ")
    except Exception:
        pass


def _on_key(event=None):
    _mark_modified()
    _update_line_count()
    actualizar_cursor()
    root.after(300, _highlight_syntax)


def bind_shortcuts():
    root.bind("<Control-o>",      lambda e: abrir_archivo())
    root.bind("<Control-s>",      lambda e: guardar_archivo())
    root.bind("<Control-Return>", lambda e: ejecutar_codigo())
    root.bind("<Control-n>",      lambda e: nuevo_archivo())
    editor.bind("<KeyRelease>",   _on_key)
    editor.bind("<ButtonRelease>", actualizar_cursor)


# ================================================================
#  VENTANA PRINCIPAL
# ================================================================
root = tk.Tk()
root.title("Compilador Rust  —  UNITEC")
root.geometry("1200x820")
root.minsize(800, 560)
root.configure(bg=C["bg"])

# ---- Menubar ----
menubar = tk.Menu(root, bg=C["bg2"], fg=C["text"],
                  activebackground=C["accent2"], activeforeground=C["text_bright"],
                  relief="flat", bd=0)

def _menu(label, items):
    m = tk.Menu(menubar, tearoff=0, bg=C["bg2"], fg=C["text"],
                activebackground=C["accent2"], activeforeground=C["text_bright"],
                relief="flat", bd=1)
    for item in items:
        if item is None:
            m.add_separator()
        else:
            m.add_command(label=item[0], command=item[1])
    menubar.add_cascade(label=label, menu=m)

_menu("Archivo", [
    ("Nuevo              Ctrl+N", nuevo_archivo),
    ("Abrir...           Ctrl+O", abrir_archivo),
    None,
    ("Guardar            Ctrl+S", guardar_archivo),
    ("Guardar como...",           guardar_como),
    None,
    ("Seleccionar compilador...", seleccionar_compilador),
    None,
    ("Salir", root.quit),
])
_menu("Ejecutar", [
    ("Analizar   Ctrl+Enter", ejecutar_codigo),
    ("Limpiar salida",         limpiar_salida),
])
root.config(menu=menubar)

# ================================================================
#  HEADER BAR
# ================================================================
header = tk.Frame(root, bg=C["bg2"], height=48)
header.pack(fill="x", side="top")
header.pack_propagate(False)

# Logo / título
tk.Label(header, text="🦀  Compilador Rust",
         bg=C["bg2"], fg=C["text_bright"],
         font=("Consolas", 13, "bold")).pack(side="left", padx=16, pady=8)

tk.Frame(header, bg=C["border"], width=1).pack(side="left", fill="y", pady=8)

# Botones
_btn(header, "  🗋  Nuevo",   nuevo_archivo).pack(side="left", padx=(8,2), pady=8)
_btn(header, "  📂  Abrir",   abrir_archivo).pack(side="left", padx=2,    pady=8)
_btn(header, "  💾  Guardar", guardar_archivo).pack(side="left", padx=2,  pady=8)

tk.Frame(header, bg=C["border"], width=1).pack(side="left", fill="y", pady=8, padx=6)

run_btn = _btn(header, "  ▶  Analizar",
               ejecutar_codigo, bg=C["run"], hover=C["run_hover"],
               fg="#ffffff")
run_btn.pack(side="left", padx=2, pady=8)

_btn(header, "  ✕  Limpiar", limpiar_salida).pack(side="left", padx=2, pady=8)

# ================================================================
#  LAYOUT PRINCIPAL
# ================================================================
pane = tk.PanedWindow(root, orient=tk.HORIZONTAL, bg=C["border"],
                      sashwidth=4, sashpad=0, sashrelief="flat")
pane.pack(fill="both", expand=True)

# ================================================================
#  PANEL IZQUIERDO — EDITOR
# ================================================================
left = tk.Frame(pane, bg=C["bg"])

# Cabecera del editor
editor_hdr = tk.Frame(left, bg=C["bg3"], height=30)
editor_hdr.pack(fill="x")
editor_hdr.pack_propagate(False)
tk.Label(editor_hdr, text="  EDITOR",
         bg=C["bg3"], fg=C["muted"],
         font=("Consolas", 8, "bold")).pack(side="left", padx=8, pady=6)

file_label = tk.Label(editor_hdr, text="sin titulo",
                      bg=C["bg3"], fg=C["muted"],
                      font=("Consolas", 8))
file_label.pack(side="left")

# Contenedor editor
editor_body = tk.Frame(left, bg=C["bg3"])
editor_body.pack(fill="both", expand=True)

mono = font.Font(family="Consolas", size=11)

# Números de línea
line_frame = tk.Frame(editor_body, bg=C["bg2"], width=46)
line_frame.pack(side="left", fill="y")
line_frame.pack_propagate(False)

line_numbers = tk.Text(line_frame, width=4,
                       bg=C["bg2"], fg=C["muted"],
                       state="disabled", font=mono, bd=0,
                       pady=6, padx=4,
                       selectbackground=C["bg2"],
                       cursor="arrow", relief="flat")
line_numbers.pack(fill="both", expand=True)

tk.Frame(editor_body, bg=C["border"], width=1).pack(side="left", fill="y")

# Editor principal
editor = scrolledtext.ScrolledText(
    editor_body,
    bg=C["bg3"], fg=C["text"],
    insertbackground=C["accent"],
    font=mono, relief="flat", bd=0,
    pady=6, padx=10,
    selectbackground="#2d4a6e",
    wrap="none", undo=True,
    tabs=("1c",))
editor.pack(fill="both", expand=True)

pane.add(left, minsize=350)

# ================================================================
#  PANEL DERECHO — SALIDA
# ================================================================
right = tk.Frame(pane, bg=C["bg"])

# Cabecera
out_hdr = tk.Frame(right, bg=C["bg3"], height=30)
out_hdr.pack(fill="x")
out_hdr.pack_propagate(False)
tk.Label(out_hdr, text="  SALIDA",
         bg=C["bg3"], fg=C["muted"],
         font=("Consolas", 8, "bold")).pack(side="left", padx=8, pady=6)

# Notebook de pestanas
style = ttk.Style()
style.theme_use("default")
style.configure("D.TNotebook",
    background=C["bg2"], borderwidth=0, tabmargins=[0,0,0,0])
style.configure("D.TNotebook.Tab",
    background=C["bg2"], foreground=C["muted"],
    padding=[16, 6], font=("Consolas", 9, "bold"),
    borderwidth=0)
style.map("D.TNotebook.Tab",
    background=[("selected", C["bg3"])],
    foreground=[("selected", C["text_bright"])])

notebook = ttk.Notebook(right, style="D.TNotebook")
notebook.pack(fill="both", expand=True)
out_font = font.Font(family="Consolas", size=10)


def _make_tab(label):
    fr = tk.Frame(notebook, bg=C["bg3"])
    notebook.add(fr, text=f"  {label}  ")
    w = scrolledtext.ScrolledText(
        fr, bg=C["bg3"], fg=C["text"],
        font=out_font, relief="flat", bd=0,
        pady=6, padx=4, state="disabled",
        wrap="none")
    w.pack(fill="both", expand=True)
    return fr, w


tab_tokens,  out_tokens  = _make_tab("Tokens")
tab_ast,     out_ast     = _make_tab("AST")
tab_console, out_console = _make_tab("Consola")

pane.add(right, minsize=300)

# ================================================================
#  SYNTAX HIGHLIGHT TAGS (editor)
# ================================================================
editor.tag_config("hl_kw",   foreground=C["purple"])
editor.tag_config("hl_type", foreground=C["cyan"])
editor.tag_config("hl_num",  foreground=C["orange"])
editor.tag_config("hl_str",  foreground=C["green"])
editor.tag_config("hl_cmt",  foreground=C["muted"])
editor.tag_config("hl_op",   foreground=C["yellow"])

# ================================================================
#  TAGS: TOKENS
# ================================================================
out_tokens.tag_config("tok_pos",   foreground=C["muted"])
out_tokens.tag_config("tok_kw",    foreground=C["purple"])
out_tokens.tag_config("tok_type",  foreground=C["cyan"])
out_tokens.tag_config("tok_lit",   foreground=C["orange"])
out_tokens.tag_config("tok_op",    foreground=C["yellow"])
out_tokens.tag_config("tok_id",    foreground=C["text_bright"])
out_tokens.tag_config("tok_delim", foreground=C["muted"])
out_tokens.tag_config("dim",       foreground=C["muted"])

# ================================================================
#  TAGS: AST
# ================================================================
out_ast.tag_config("ast_fn",     foreground=C["accent"],  font=("Consolas", 10, "bold"))
out_ast.tag_config("ast_let",    foreground=C["purple"])
out_ast.tag_config("ast_ctrl",   foreground=C["yellow"])
out_ast.tag_config("ast_op",     foreground=C["orange"])
out_ast.tag_config("ast_call",   foreground=C["green"])
out_ast.tag_config("ast_lit",    foreground=C["orange"])
out_ast.tag_config("ast_id",     foreground=C["text_bright"])
out_ast.tag_config("ast_struct", foreground=C["muted"],   font=("Consolas", 10, "bold"))
out_ast.tag_config("ast_dim",    foreground=C["text"])

# ================================================================
#  TAGS: CONSOLA
# ================================================================
out_console.tag_config("success",    foreground=C["green"],  font=("Consolas", 10, "bold"))
out_console.tag_config("error",      foreground=C["red"])
out_console.tag_config("warning",    foreground=C["yellow"])
out_console.tag_config("info",       foreground=C["cyan"])
out_console.tag_config("section_hdr",foreground=C["muted"],  font=("Consolas", 9, "bold"))
out_console.tag_config("dim",        foreground=C["muted"])
out_console.tag_config("normal",     foreground=C["text"])

# ================================================================
#  BARRA DE ESTADO
# ================================================================
statusbar = tk.Frame(root, bg=C["bg2"], height=26)
statusbar.pack(fill="x", side="bottom")
statusbar.pack_propagate(False)

# Indicador de compilador
compiler_indicator = tk.Label(statusbar, text="",
    bg=C["bg2"], fg=C["muted"], font=("Consolas", 8))
compiler_indicator.pack(side="right", padx=10)

cursor_label = tk.Label(statusbar, text="  Ln 1  Col 1  ",
    bg=C["bg2"], fg=C["muted"], font=("Consolas", 8))
cursor_label.pack(side="right")

tk.Frame(statusbar, bg=C["border"], width=1).pack(side="right", fill="y", pady=4)

status_label = tk.Label(statusbar, text="  Listo",
    bg=C["bg2"], fg=C["text"], font=("Consolas", 9), anchor="w")
status_label.pack(side="left", fill="x", expand=True)

# ================================================================
#  CODIGO INICIAL
# ================================================================
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

# ================================================================
#  ARRANQUE
# ================================================================
compiler_path = find_compiler()
if compiler_path:
    actualizar_estado("  Compilador listo")
    compiler_indicator.config(
        text=f"  ● {os.path.basename(os.path.dirname(compiler_path))}/compiler  ",
        fg=C["green"])
else:
    actualizar_estado("  Ejecuta 'make' para construir el compilador")
    compiler_indicator.config(text="  ○ sin compilador  ", fg=C["red"])

bind_shortcuts()
_update_line_count()
_highlight_syntax()
root.mainloop()
