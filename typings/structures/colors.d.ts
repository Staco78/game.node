export declare class Color {
    constructor(color: ColorResolvable);
    constructor(r: number, g: number, b: number);

    r: number;
    g: number;
    b: number;
}

export type ColorResolvable = Color | [number, number, number] | { r: number; g: number; b: number };
