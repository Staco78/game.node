import { ColorResolvable } from "../structures/colors";
import { Texture } from "../structures/texture";

export declare class Rect {
    constructor(x: number, y: number, width: number, height: number);

    x: number;
    y: number;

    width: number;
    height: number;

    get color(): { r: number; g: number; b: number };
    set color(value: ColorResolvable);

    setTexture(texture: Texture): void;
}
