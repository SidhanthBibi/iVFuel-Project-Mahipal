export function Button({ children, onClick, variant }) {
    const baseStyle =
      "px-4 py-2 rounded-lg font-semibold transition shadow hover:opacity-90";
    const variantStyle =
      variant === "outline"
        ? "bg-white text-indigo-700 hover:bg-indigo-200"
        : "bg-indigo-700 text-white";
  
    return (
      <button onClick={onClick} className={`${baseStyle} ${variantStyle}`}>
        {children}
      </button>
    );
  }
  