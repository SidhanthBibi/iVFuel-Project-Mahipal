// index/api/data.js

export async function GET() {
  try {
    const url = process.env.KV_REST_API_URL;
    const token = process.env.KV_REST_API_TOKEN;

    const response = await fetch(`${url}/get/fuelData`, {
      headers: {
        Authorization: `Bearer ${token}`,
      },
      cache: "no-store",
    });

    if (!response.ok) {
      return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 500 });
    }

    const raw = await response.json();
    const { result } = raw;

    if (!result) {
      return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 200 });
    }

    const { flow, total } = JSON.parse(result);
    return new Response(JSON.stringify({ flow, total }), { status: 200 });
  } catch (err) {
    console.error("GET /api/data error:", err);
    return new Response(JSON.stringify({ flow: 0, total: 0 }), { status: 500 });
  }
}
