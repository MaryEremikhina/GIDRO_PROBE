from requests import get

coordinate_st = [38.0301, 75.124]
coordinates_con1 = [30.7854, 60.4765]
coordinates_con2 = [40.7854, 40.4765]
response = get("https://static-maps.yandex.ru/1.x/?"
             f"ll={coordinate_st[0] - 10},{coordinate_st[1] - 10}&"
             f"spn={coordinate_st[0]},{coordinate_st[1]}&"
             "z=0&"
             "size=600,450&"
             f"pt={coordinate_st[0]},{coordinate_st[1]},vkgrm~{coordinates_con1[0]},{coordinates_con1[1]},vkgrm~{coordinates_con2[0]},{coordinates_con2[1]},vkbkm&"
             f"pl=c:960018,w:1,{coordinate_st[0]},{coordinate_st[1]},{coordinates_con1[0]},{coordinates_con1[1]},{coordinates_con2[0]},{coordinates_con2[1]}&"
             "l=map")


with open("map.png", "wb") as file:
    file.write(response.content)