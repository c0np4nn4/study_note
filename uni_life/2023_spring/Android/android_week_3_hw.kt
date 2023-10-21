import java.lang.NumberFormatException
import java.util.*

class example5 {
}

fun getMenu(): String? {
    println("============= MENU ==============")
    println("| (1) 참깨라면    - 1,000 원      |")
    println("| (2) 햄버거      - 1,500 원      |")
    println("| (3) 콜라        - 8000 원      |")
    println("| (4) 핫바       - 1,200 원      |")
    println("| (5) 초코우유    - 1,500 원      |")
    println("Choose menu: ")
    val sc: Scanner = Scanner(System.`in`)
    var select: String? = sc.nextLine()

    return select
}

fun getChange(money: Int, cost: Int): Int {
    var change = money - cost

    return change
}

fun getPrice(menu_id: String?): Int {
    if (menu_id == "1") {
        println("참깨라면이 선택되었습니다.")
        return 1000
    }
    else if (menu_id == "2") {
        println("햄버거가 선택되었습니다.")
        return 1500
    }
    else if (menu_id == "3") {
        println("콜라가 선택되었습니다.")
        return 800
    }
    else if (menu_id == "4") {
        println("핫바가 선택되었습니다.")
        return 1200
    }
    else if (menu_id == "5") {
        println("초코우유가 선택되었습니다.")
        return 1500
    }
    else {
        println("아무것도 선택하지 않았습니다.")
        return -1
    }
}

fun getCoin(): Int? {
    println("Insert Coin")
    val sc: Scanner = Scanner(System.`in`)
    var coin_str: String? = sc.nextLine()

    var coin: Int? = null

    try {
        coin = coin_str!!.toInt()
        println("${coin} 원을 넣었습니다.")
    } catch(e:NumberFormatException) {
        println("돈을 넣지 않았습니다.")
        println("다시 돈을 넣어주세요.")
    }

    return coin
}

fun main() {
    while (true) {
        var select: String? = getMenu()

        var price = getPrice(select)

        if (price == -1) {
            println("다시 선택해주세요.")
            continue
        }

        var coin: Int? = null
        while (coin == null) {
            coin = getCoin()
        }

        var change = getChange(coin, price)

        if (change > 0) {
            println("감사합니다. 잔돈반환:${change}")
        } else {
            println("현금이 부족합니다.")
            break
        }
    }
}
