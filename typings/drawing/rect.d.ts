import { ColorResolvable } from "../structures/colors";

export declare class Rect {
    constructor(x: number, y: number, width: number, height: number);

    x: number;
    y: number;

    width: number;
    height: number;

    get color(): { r: number; g: number; b: number };
    set color(value: ColorResolvable);
}
