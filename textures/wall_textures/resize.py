import os
from PIL import Image
import glob

def create_lowres_images(root_dir='.'):
    """
    Create low-resolution versions of all PNG images in directory structure.
    Reduces size by 80% (from ~512px to ~102px) and adds '_lr' postfix.
    Preserves transparency and handles alpha channels properly.
    """
    # Find all PNG files recursively
    png_files = glob.glob(os.path.join(root_dir, '**', '*.png'), recursive=True)
    
    # Filter out specific directories if needed
    filtered_png_files = []
    for png_path in png_files:
        # Skip files that are already low-res
        if '_lr.png' in png_path:
            continue
        filtered_png_files.append(png_path)
    
    print(f"Processing {len(filtered_png_files)} PNG files...")
    
    for png_path in filtered_png_files:
        try:
            # Open and process the image
            with Image.open(png_path) as img:
                # Convert to RGBA if necessary to preserve transparency
                if img.mode != 'RGBA':
                    img = img.convert('RGBA')
                
                # Calculate new size (80% reduction = 20% of original)
                original_width, original_height = img.size
                new_width = max(1, int(original_width * 0.50))
                new_height = max(1, int(original_height * 0.50))
                
                # Create a transparent background image
                resized_img = Image.new('RGBA', (new_width, new_height), (0, 0, 0, 0))
                
                # Resize the original image using LANCZOS
                temp_resized = img.resize((new_width, new_height), Image.Resampling.LANCZOS)
                
                # Composite the resized image onto transparent background
                resized_img = Image.alpha_composite(resized_img, temp_resized)
                
                # Create output filename with '_lr' postfix
                directory, filename = os.path.split(png_path)
                name, ext = os.path.splitext(filename)
                output_filename = f"{name}_lr{ext}"
                output_path = os.path.join(directory, output_filename)
                
                # Save the low-res image with optimization and transparency
                resized_img.save(output_path, 'PNG', optimize=True)
                
                print(f"Created: {output_path} ({original_width}x{original_height} -> {new_width}x{new_height})")
                
        except Exception as e:
            print(f"Error processing {png_path}: {e}")

def create_lowres_images_alternative(root_dir='.'):
    """
    Alternative method: Use NEAREST filter for pixel art (no anti-aliasing)
    This preserves hard edges and prevents blending artifacts.
    """
    # Find all PNG files recursively
    png_files = glob.glob(os.path.join(root_dir, '**', '*.png'), recursive=True)
    
    filtered_png_files = []
    for png_path in png_files:
        if '_lr.png' in png_path:
            continue
        filtered_png_files.append(png_path)
    
    print(f"Processing {len(filtered_png_files)} PNG files with NEAREST filter...")
    
    for png_path in filtered_png_files:
        try:
            # Open and process the image
            with Image.open(png_path) as img:
                # Convert to RGBA if necessary to preserve transparency
                if img.mode != 'RGBA':
                    img = img.convert('RGBA')
                
                # Calculate new size (80% reduction = 20% of original)
                original_width, original_height = img.size
                new_width = max(1, int(original_width * 0.50))
                new_height = max(1, int(original_height * 0.50))
                
                # Use NEAREST filter for pixel art (no anti-aliasing)
                resized_img = img.resize((new_width, new_height), Image.Resampling.NEAREST)
                
                # Create output filename with '_lr' postfix
                directory, filename = os.path.split(png_path)
                name, ext = os.path.splitext(filename)
                output_filename = f"{name}_lr{ext}"
                output_path = os.path.join(directory, output_filename)
                
                # Save the low-res image
                resized_img.save(output_path, 'PNG', optimize=True)
                
                print(f"Created (NEAREST): {output_path} ({original_width}x{original_height} -> {new_width}x{new_height})")
                
        except Exception as e:
            print(f"Error processing {png_path}: {e}")

def process_by_category(root_dir='.'):
    """
    Process textures by category with specific settings for each type.
    """
    categories = {
        'enemy_animations': ['animation_enemy/**/*.png'],
        'wall_textures': ['textures/wall_textures/*.png'],
        'med_kit': ['med_kit.png']
    }
    
    total_processed = 0
    
    for category, patterns in categories.items():
        print(f"\n--- Processing {category} ---")
        
        category_files = []
        for pattern in patterns:
            full_pattern = os.path.join(root_dir, pattern)
            files = glob.glob(full_pattern, recursive=True)
            # Filter out low-res files
            files = [f for f in files if '_lr.png' not in f]
            category_files.extend(files)
        
        print(f"Found {len(category_files)} files in {category}")
        
        for png_path in category_files:
            try:
                with Image.open(png_path) as img:
                    # Convert to RGBA if necessary
                    if img.mode != 'RGBA':
                        img = img.convert('RGBA')
                    
                    # Calculate new size
                    original_width, original_height = img.size
                    new_width = max(1, int(original_width * 0.20))
                    new_height = max(1, int(original_height * 0.20))
                    
                    # Use NEAREST for pixel art style, LANCZOS for smooth textures
                    if 'wall' in category:
                        # Use NEAREST for wall textures to preserve sharp edges
                        resized_img = img.resize((new_width, new_height), Image.Resampling.NEAREST)
                    else:
                        # Use LANCZOS for other textures
                        resized_img = img.resize((new_width, new_height), Image.Resampling.LANCZOS)
                    
                    # Create output filename
                    directory, filename = os.path.split(png_path)
                    name, ext = os.path.splitext(filename)
                    output_filename = f"{name}_lr{ext}"
                    output_path = os.path.join(directory, output_filename)
                    
                    # Save the low-res image
                    resized_img.save(output_path, 'PNG', optimize=True)
                    
                    filter_type = "NEAREST" if 'wall' in category else "LANCZOS"
                    print(f"  {filter_type}: {output_path} ({original_width}x{original_height} -> {new_width}x{new_height})")
                    total_processed += 1
                    
            except Exception as e:
                print(f"Error processing {png_path}: {e}")
    
    print(f"\nTotal files processed: {total_processed}")

def list_textures(root_dir='.'):
    """
    List all textures found in the project structure.
    """
    categories = {
        'Enemy Animations': ['animation_enemy/**/*.png'],
        'Wall Textures': ['textures/wall_textures/*.png'], 
        'Items': ['med_kit.png'],
        'All Other PNGs': ['**/*.png']
    }
    
    print("Texture Inventory:")
    print("=" * 50)
    
    total_count = 0
    for category, patterns in categories.items():
        category_files = set()
        for pattern in patterns:
            full_pattern = os.path.join(root_dir, pattern)
            files = glob.glob(full_pattern, recursive=True)
            # Filter out low-res files
            files = [f for f in files if '_lr.png' not in f]
            category_files.update(files)
        
        if category_files:
            print(f"\n{category} ({len(category_files)} files):")
            for file in sorted(category_files):
                with Image.open(file) as img:
                    size = f"{img.size[0]}x{img.size[1]}"
                print(f"  {file} [{size}]")
            total_count += len(category_files)
    
    print(f"\nTotal textures found: {total_count}")

def cleanup_lowres_images(root_dir='.'):
    """
    Delete all low-resolution textures with '_lr' postfix.
    """
    # Find all low-res PNG files recursively
    lr_files = glob.glob(os.path.join(root_dir, '**', '*_lr.png'), recursive=True)
    
    if not lr_files:
        print("No low-resolution textures found to delete.")
        return
    
    print(f"Found {len(lr_files)} low-resolution texture(s) to delete:")
    
    for lr_file in lr_files:
        try:
            os.remove(lr_file)
            print(f"Deleted: {lr_file}")
        except Exception as e:
            print(f"Error deleting {lr_file}: {e}")
    
    print(f"Cleanup completed. Deleted {len(lr_files)} file(s).")

def main():
    import sys
    
    if len(sys.argv) < 2:
        print("Usage: python create_lowres.py [create|create_pixel|create_categories|list|cleanup]")
        print("  create           - Generate low-res versions with transparency (LANCZOS)")
        print("  create_pixel      - Generate low-res versions for pixel art (NEAREST)")
        print("  create_categories - Process by category with optimal filters")
        print("  list             - List all textures found in project")
        print("  cleanup          - Delete all existing low-resolution textures")
        sys.exit(1)
    
    command = sys.argv[1].lower()
    
    if command == 'create':
        print("Creating low-resolution versions of all PNG files...")
        print("Reducing size by 80% (20% of original dimensions)")
        print("Using LANCZOS filter with transparency preservation")
        create_lowres_images()
        print("Done!")
    elif command == 'create_pixel':
        print("Creating low-resolution versions for pixel art...")
        print("Reducing size by 80% (20% of original dimensions)")
        print("Using NEAREST filter (no anti-aliasing)")
        create_lowres_images_alternative()
        print("Done!")
    elif command == 'create_categories':
        print("Processing textures by category with optimal filters...")
        print("Wall textures: NEAREST filter (pixel art)")
        print("Other textures: LANCZOS filter (smooth)")
        process_by_category()
        print("Done!")
    elif command == 'list':
        list_textures()
    elif command == 'cleanup':
        print("Cleaning up all low-resolution textures...")
        cleanup_lowres_images()
    else:
        print(f"Unknown command: {command}")
        print("Usage: python create_lowres.py [create|create_pixel|create_categories|list|cleanup]")
        sys.exit(1)

if __name__ == "__main__":
    main()