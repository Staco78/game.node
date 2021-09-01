export declare class Vector2d {
    constructor(size: Vector2dResolvable);
    constructor(x: number, y: number);

    x: number;
    y: number;
}

export type Vector2dResolvable = { x: number; y: number } | [number, number];
