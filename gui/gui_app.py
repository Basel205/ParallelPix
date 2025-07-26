# # gui/gui_app.py
# import tkinter as tk
# from tkinter import filedialog, ttk, messagebox
# import subprocess
# import os

# class ImageProcessorGUI:
#     def __init__(self, root):
#         self.root = root
#         self.root.title("Image Processing Toolkit")
        
#         # Initialize variables
#         self.input_path = tk.StringVar()
#         self.filter_var = tk.StringVar(value="blur")
#         self.parallel_var = tk.BooleanVar(value=True)
        
#         # Create GUI elements
#         self.create_widgets()
    
#     def create_widgets(self):
#         # Input file selection
#         ttk.Label(self.root, text="Input Image:").grid(row=0, column=0, padx=5, pady=5)
#         ttk.Entry(self.root, textvariable=self.input_path, width=40).grid(row=0, column=1, padx=5)
#         ttk.Button(self.root, text="Browse", command=self.browse_file).grid(row=0, column=2, padx=5)
        
#         # Filter selection
#         ttk.Label(self.root, text="Filter:").grid(row=1, column=0, padx=5, pady=5)
#         filter_combo = ttk.Combobox(self.root, textvariable=self.filter_var, 
#                                    values=["blur", "anime", "oil", "pencil", "thermal"])
#         filter_combo.grid(row=1, column=1, sticky="w", padx=5)
        
#         # Parallel processing checkbox
#         ttk.Checkbutton(self.root, text="Parallel Processing", variable=self.parallel_var).grid(row=2, column=1, sticky="w", padx=5)
        
#         # Process button
#         ttk.Button(self.root, text="Process Image", command=self.process_image).grid(row=3, column=1, pady=10)
        
#     def browse_file(self):
#         file_path = filedialog.askopenfilename(
#             title="Select Input Image",
#             filetypes=[("Image Files", "*.jpg *.jpeg *.png")]
#         )
#         if file_path:
#             self.input_path.set(file_path)

# def process_image(self):
#     input_path = self.input_path.get()
#     if not input_path:
#         messagebox.showerror("Error", "Please select an input image!")
#         return

#     # Ensure output directory exists
#     output_dir = os.path.join(os.path.dirname(__file__), "..", "output")
#     os.makedirs(output_dir, exist_ok=True)
#     output_path = os.path.join(output_dir, "processed_image.jpg")

#     # Full path to the executable
#     exe_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "Release", "ImageProcessingOpenMP.exe"))

#     # Construct command
#     cmd = [
#         exe_path,
#         input_path,
#         output_path,
#         self.filter_var.get(),
#         "--parallel" if self.parallel_var.get() else ""
#     ]

#     try:
#         result = subprocess.run(cmd, check=True, capture_output=True, text=True)
#         messagebox.showinfo("Success", f"Image processed successfully!\n{result.stdout}")
#     except FileNotFoundError:
#         messagebox.showerror("Error", f"Executable not found at: {exe_path}")
#     except subprocess.CalledProcessError as e:
#         messagebox.showerror("Error", f"Processing failed:\n{e.stderr}")

    
#     # def process_image(self):
#     #     input_path = self.input_path.get()
#     #     if not input_path:
#     #         messagebox.showerror("Error", "Please select an input image!")
#     #         return
            
#     #     output_dir = os.path.join(os.path.dirname(__file__), "..", "output")
#     #     os.makedirs(output_dir, exist_ok=True)
#     #     output_path = os.path.join(output_dir, "processed_image.jpg")
        
#     #     cmd = [
#     #         "ImageProcessingOpenMP.exe",
#     #         input_path,
#     #         output_path,
#     #         self.filter_var.get(),
#     #         "--parallel" if self.parallel_var.get() else ""
#     #     ]
        
#     #     try:
#     #         result = subprocess.run(cmd, check=True, capture_output=True, text=True)
#     #         messagebox.showinfo("Success", f"Image processed successfully!\n{result.stdout}")
#     #     except subprocess.CalledProcessError as e:
#     #         messagebox.showerror("Error", f"Processing failed:\n{e.stderr}")

# if __name__ == "__main__":
#     root = tk.Tk()
#     app = ImageProcessorGUI(root)
#     root.mainloop()




# gui/gui_app.py
import tkinter as tk
from tkinter import filedialog, ttk, messagebox
import subprocess
import os

class ImageProcessorGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Image Processing Toolkit")
        
        # Initialize variables
        self.input_path = tk.StringVar()
        self.filter_var = tk.StringVar(value="blur")
        self.parallel_var = tk.BooleanVar(value=True)
        
        # Create GUI elements
        self.create_widgets()
    
    def create_widgets(self):
        # Input file selection
        ttk.Label(self.root, text="Input Image:").grid(row=0, column=0, padx=5, pady=5)
        ttk.Entry(self.root, textvariable=self.input_path, width=40).grid(row=0, column=1, padx=5)
        ttk.Button(self.root, text="Browse", command=self.browse_file).grid(row=0, column=2, padx=5)
        
        # Filter selection
        ttk.Label(self.root, text="Filter:").grid(row=1, column=0, padx=5, pady=5)
        filter_combo = ttk.Combobox(self.root, textvariable=self.filter_var, 
                                   values=["blur", "anime", "oil", "pencil", "thermal"])
        filter_combo.grid(row=1, column=1, sticky="w", padx=5)
        
        # Parallel processing checkbox
        ttk.Checkbutton(self.root, text="Parallel Processing", variable=self.parallel_var).grid(row=2, column=1, sticky="w", padx=5)
        
        # Process button
        ttk.Button(self.root, text="Process Image", command=self.process_image).grid(row=3, column=1, pady=10)
        
    def browse_file(self):
        file_path = filedialog.askopenfilename(
            title="Select Input Image",
            filetypes=[("Image Files", "*.jpg *.jpeg *.png")]
        )
        if file_path:
            self.input_path.set(file_path)
    
    def process_image(self):  # Correct indentation
        input_path = self.input_path.get()
        if not input_path:
            messagebox.showerror("Error", "Please select an input image!")
            return

        # Ensure output directory exists
        output_dir = os.path.join(os.path.dirname(__file__), "..", "output")
        os.makedirs(output_dir, exist_ok=True)
        output_path = os.path.join(output_dir, "processed_image.jpg")

        # Full path to the executable
        exe_path = os.path.abspath(os.path.join(
            os.path.dirname(__file__), 
            "..", 
            "build", 
            "Release", 
            "ImageProcessingOpenMP.exe"
        ))

        # Construct command
        cmd = [
            exe_path,
            input_path,
            output_path,
            self.filter_var.get(),
            "--parallel" if self.parallel_var.get() else ""
        ]

        try:
            result = subprocess.run(cmd, check=True, capture_output=True, text=True)
            messagebox.showinfo("Success", f"Image processed successfully!\n{result.stdout}")
        except FileNotFoundError:
            messagebox.showerror("Error", f"Executable not found at:\n{exe_path}")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Processing failed:\n{e.stderr}")

if __name__ == "__main__":
    root = tk.Tk()
    app = ImageProcessorGUI(root)
    root.mainloop()
