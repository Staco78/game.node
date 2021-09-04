module.exports = require("./build/Debug/binding");

Object.setPrototypeOf(module.exports.Rect.prototype, module.exports.Shape.prototype);
Object.setPrototypeOf(module.exports.Rect, module.exports.Shape);

module.exports.Event = {
    Closed: 0, //!< The window requested to be closed (no data)
    Resized: 1, //!< The window was resized (data in event.size)
    LostFocus: 2, //!< The window lost the focus (no data)
    GainedFocus: 3, //!< The window gained the focus (no data)
    TextEntered: 4, //!< A character was entered (data in event.text)
    KeyPressed: 5, //!< A key was pressed (data in event.key)
    KeyReleased: 6, //!< A key was released (data in event.key)
    MouseWheelMoved: 7, //!< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
    MouseWheelScrolled: 8, //!< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    MouseButtonPressed: 9, //!< A mouse button was pressed (data in event.mouseButton)
    MouseButtonReleased: 10, //!< A mouse button was released (data in event.mouseButton)
    MouseMoved: 11, //!< The mouse cursor moved (data in event.mouseMove)
    MouseEntered: 12, //!< The mouse cursor entered the area of the window (no data)
    MouseLeft: 13, //!< The mouse cursor left the area of the window (no data)
    JoystickButtonPressed: 14, //!< A joystick button was pressed (data in event.joystickButton)
    JoystickButtonReleased: 15, //!< A joystick button was released (data in event.joystickButton)
    JoystickMoved: 16, //!< The joystick moved along an axis (data in event.joystickMove)
    JoystickConnected: 17, //!< A joystick was connected (data in event.joystickConnect)
    JoystickDisconnected: 18, //!< A joystick was disconnected (data in event.joystickConnect)
    TouchBegan: 19, //!< A touch event began (data in event.touch)
    TouchMoved: 22, //!< A touch moved (data in event.touch)
    TouchEnded: 21, //!< A touch event ended (data in event.touch)
    SensorChanged: 22,
};

module.exports.Color = class Color {
    constructor(color, color2, color3) {
        const err_msg = "Color must be an array of three numbers, a Color or 3 numbers";
        if (Array.isArray(color)) {
            if (color.length !== 3) throw new TypeError(err_msg);

            for (const c of color) {
                if (typeof c !== "number") throw new TypeError(err_msg);
                if (c > 255 || c < 0) throw new TypeError("A color channel must be between 0 and 255");
            }

            this.r = color[0];
            this.g = color[1];
            this.b = color[2];
        } else if (typeof color === "object" && "r" in color && "g" in color && "b" in color) {
            for (const c of color) {
                if (typeof c !== "number") throw new TypeError(err_msg);
                if (c > 255 || c < 0) throw new TypeError("A color channel must be between 0 and 255");
            }

            this.r = color.r;
            this.g = color.g;
            this.b = color.b;
        } else if (typeof color === "number" && typeof color2 === "number" && typeof color3 === "number") {
            if (color > 255 || color < 0 || color2 > 255 || color2 < 0 || color3 > 255 || color3 < 0)
                throw new TypeError("A color channel must be between 0 and 255");

            this.r = color;
            this.g = color2;
            this.b = color3;
        } else throw new TypeError(err_msg);
    }
};
